#include "../minishell.h"

void execute_builtin(t_cmd *cmd)
{
    if (cmd->pipe_i == 0 && cmd->pipe_o == 0)
        handle_redir(cmd);
    if (cmd->type == 1)
        ex_echo(cmd);
    else if (cmd->type == 2)
        ex_cd(cmd);
    else if (cmd->type == 3)
        ex_pwd();
    else if (cmd->type == 4)
        ex_export(cmd);
    else if (cmd->type == 5)
        ex_unset(cmd);
    else if (cmd->type == 6)
        ex_env();
    else if (cmd->type == 7)
        exit(0);
    if (cmd->pipe_i > 0 || cmd->pipe_o > 0)
        exit(0);
}

void execute_child_cmd(t_all_cmd *all_cmd, int i)
{
    handle_pipe(all_cmd, i);
    handle_redir(&all_cmd->cmds[i]);
    close_pipes(all_cmd);
    if ((all_cmd->cmds[i].fd_i != STDIN_FILENO))
        close(all_cmd->cmds[i].fd_i);
    if (all_cmd->cmds[i].type > 0)
        execute_builtin(&all_cmd->cmds[i]);
    if (all_cmd->cmds[i].type == 0)
        execve(all_cmd->cmds[i].cmd[0], all_cmd->cmds[i].cmd, env);
    perror("exec");
}

pid_t execute_cmd(t_all_cmd *all_cmd, int i)
{
    pid_t cmd_pid;

    cmd_pid = fork();
    if (cmd_pid == -1)
        return (0);
    if (!cmd_pid)
        execute_child_cmd(all_cmd, i);
    return (cmd_pid);
}

void execute(t_all_cmd *all_cmd)
{
    pid_t cmd_pid;
    int pid, status;
    int i;
    
    if (all_cmd->nbrcmd > 1)
        init_pipes(all_cmd);
    else if (all_cmd->nbrcmd == 1 && all_cmd->cmds[0].type > 0)
    {
        execute_builtin(&all_cmd->cmds[0]);
        return ;
    }
    i = -1;
    while(++i < all_cmd->nbrcmd)
        cmd_pid = execute_cmd(all_cmd, i);
    close_pipes(all_cmd);
    //free_pipe(all_cmd);
    waitpid(-1, &status, 0);
    waitpid(cmd_pid, &status, 0);
}