#include "../../includes/minishell.h"

void handle_redir(t_cmd *cmd)
{
    if (cmd->fd_i != 0)
    {
        cmd->saved_stdin = dup(STDIN_FILENO);
        if (dup2(cmd->fd_i, STDIN_FILENO) == -1)
            return (perror("dup"));
        close(cmd->fd_i);
    }
    if (cmd->fd_o != 1)
    {
        cmd->saved_stdout = dup(STDOUT_FILENO);
        if (dup2(cmd->fd_o, STDOUT_FILENO) == -1)
            return (perror("dup"));
        close(cmd->fd_o);
    }
}

void handle_redir_fork(t_cmd *cmd)
{
    if (cmd->fd_i != 0)
    {
        if (dup2(cmd->fd_i, STDIN_FILENO) == -1)
            return (perror("dup"));
        close(cmd->fd_i);
    }
    if (cmd->fd_o != 1)
    {
        cmd->saved_stdout = dup(STDOUT_FILENO);
        if (dup2(cmd->fd_o, STDOUT_FILENO) == -1)
            return (perror("dup"));
        close(cmd->fd_o);
    }
}