#include "minishell.h"

void execute_builtin(t_cmd *cmd)
{
    handle_redir(cmd);

}

int execute_child_cmd(t_cmd *cmd)
{
    int status;

    handle_redir(cmd);
    if (cmd->cmd)
        execve(cmd->cmd[0], cmd->cmd, env);
    perror("execve");
}

void execute_cmd(t_cmd *cmd)
{
    pid_t cmd_pid;

    cmd_pid = fork();
    if (cmd_pid == -1)
        return (perror("fork"));
    if (!cmd_pid)
        execute_child_cmd(cmd);

}

int execute(t_all_cmd *all_cmd)
{
    int i;
    int ret;

    if (all_cmd->is_pipe)
        pipe(all_cmd->pipefd);
    i= 0;
    while(i < all_cmd->nbrcmd)
    {
        handle_pipe(&all_cmd->cmds[i], all_cmd->pipefd);
        if (all_cmd->cmds->type > 0)
            execute_builtin(&all_cmd->cmds[i]);
        else if (all_cmd->cmds->type == 0)
            execute_cmd(&all_cmd->cmds[i]);
        i++;
        //...
    }
}
