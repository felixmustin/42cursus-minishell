#include "minishell.h"


int change_fd(t_all_cmd *all_cmd, int i)
{
    if (all_cmd->cmds[i].fd_i != 0)
        dup2(all_cmd->cmds[i].fd_i, STDIN_FILENO);
    if (all_cmd->cmds[i].fd_o != 0)
        dup2(all_cmd->cmds[i].fd_i, STDOUT_FILENO);
    if (all_cmd->cmds[i].pipe_i != 0)
        dup2(all_cmd->pipe[0], STDIN_FILENO);
    if (all_cmd->cmds[i].pipe_o != 0)
        dup2(all_cmd->pipe[1], STDOUT_FILENO);
    //...
}

int execute(t_all_cmd *all_cmd)
{
    int i;

    if (all_cmd->is_pipe)
        pipe(all_cmd->pipe);
    i= 0;
    while(i < all_cmd->nbrcmd)
    {
        change_fd(all_cmd, i);
        if (all_cmd->cmds->type > 0)
            exec_builtin(all_cmd);
        else if (all_cmd->cmds->type == 0)
            exec_cmd(all_cmd);
        //...
    }
}
