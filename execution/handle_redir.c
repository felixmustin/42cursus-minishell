#include "../minishell.h"

void handle_redir(t_cmd *cmd)
{
    if (cmd->fd_i != 0)
    {
        if (dup2(cmd->fd_i, STDIN_FILENO) == -1)
            return (perror("dup"));
    }
    if (cmd->fd_o != 1)
    {
        if (dup2(cmd->fd_o, STDOUT_FILENO) == -1)
            return (perror("dup"));
    }
}
