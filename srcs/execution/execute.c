#include "../../includes/minishell.h"

void execute_builtin(t_all_cmd *all_cmd, int i)
{
    if (all_cmd->cmds[i].pipe_i == 0 && all_cmd->cmds[i].pipe_o == 0)
        handle_redir(&all_cmd->cmds[i]);
    if (all_cmd->cmds[i].type == 1)
        ex_echo(all_cmd, i);
    else if (all_cmd->cmds[i].type == 2)
        ex_cd(all_cmd, i);
    else if (all_cmd->cmds[i].type == 3)
        ex_pwd(all_cmd, i);
    else if (all_cmd->cmds[i].type == 4)
        ex_export(all_cmd, i);
    else if (all_cmd->cmds[i].type == 5)
        ex_unset(all_cmd, i);
    else if (all_cmd->cmds[i].type == 6)
        ex_env(all_cmd, i);
    else if (all_cmd->cmds[i].type == 7)
        ex_exit(all_cmd, i);
    if (all_cmd->cmds[i].pipe_i > 0 || all_cmd->cmds[i].pipe_o > 0)
        exit(all_cmd->status);
}

void execute_child_cmd(t_all_cmd *all_cmd, int i)
{
    handle_pipe(all_cmd, i);
    handle_redir_fork(&all_cmd->cmds[i]);
    close_pipes(all_cmd);
    if (all_cmd->cmds[i].type > 0)
        execute_builtin(all_cmd, i);
    if (all_cmd->cmds[i].type == 0)
        execve(all_cmd->cmds[i].cmd[0], all_cmd->cmds[i].cmd, env);
    exit(errno);
}

void execute_cmd(t_all_cmd *all_cmd, int i)
{
    all_cmd->pids[i] = fork();
    if (all_cmd->pids[i]== -1)
        return ;
    if (!all_cmd->pids[i])
        execute_child_cmd(all_cmd, i);
}

void execute(t_all_cmd *all_cmd)
{
    int i;
    
    i = -1;
    cmd_signals();
    if (all_cmd->nbrcmd > 1)
        init_pipes(all_cmd);
    else if (all_cmd->nbrcmd == 1 && all_cmd->cmds[0].type > 0)
    {
        execute_builtin(all_cmd, 0);
        exit_cmds(all_cmd, 1);
        return ;
    }
    while(++i < all_cmd->nbrcmd)
        execute_cmd(all_cmd, i);
    exit_cmds(all_cmd, i);
    return ;
}