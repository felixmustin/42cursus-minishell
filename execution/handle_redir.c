#include "minishell.h"

void handle_redir(t_all_cmd *all_cmd, int i)
{
    if (all_cmd->cmds[i].fd_i != 0)
    {
        if (dup2(all_cmd->cmds[i].fd_i, STDIN_FILENO) == -1)
            return (perror("dup"));
    }
    if (all_cmd->cmds[i].fd_o != 1)
    {
        if (dup2(all_cmd->cmds[i].fd_o, STDOUT_FILENO) == -1)
            return (perror("dup"));
    }
}
