#include "minishell.h"

void execute_builtin(t_cmd *cmd)
{
    if (cmd->type == 1)
        ex_echo(cmd);
    if (cmd->type == 2)
        ex_cd(cmd);
    if (cmd->type == 3)
        ex_pwd();
    /*if (cmd->type == 4)
        ex_export();
    if (cmd->type == 5)
        ex_unset();*/
    if (cmd->type == 6)
        ex_env();
    /*if (cmd->type == 7)
        ex_exit();*/
    exit(0);
}

void execute_child_cmd(t_all_cmd *all_cmd, int i)
{
    handle_pipe(all_cmd, i);
    handle_redir(all_cmd, i);
    close_pipes(all_cmd);
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
        all_cmd->pipefd = init_pipes(all_cmd->nbrcmd - 1);
    i = -1;
    while(++i < all_cmd->nbrcmd)
    {
        cmd_pid = execute_cmd(all_cmd, i);
    }
    close_pipes(all_cmd);
    /*while ((pid = wait(&status)) != -1)	//pick up all the dead children
		fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));*/
    waitpid(-1, &status, 0);
    waitpid(cmd_pid, &status, 0);
	//free(all_cmd->pipefd);
}