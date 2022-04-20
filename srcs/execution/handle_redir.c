#include "../../includes/minishell.h"

int handle_redir(t_all_cmd *all_cmd, int i)
{
    if (all_cmd->cmds[i].fd_i != 0)
    {
        all_cmd->cmds[i].saved_stdin = dup(STDIN_FILENO);
        if (dup2(all_cmd->cmds[i].fd_i, STDIN_FILENO) == -1)
        {
            all_cmd->status = 1;
            return (errno);
        }
        close(all_cmd->cmds[i].fd_i);
    }
    if (all_cmd->cmds[i].fd_o != 1)
    {
        all_cmd->cmds[i].saved_stdout = dup(STDOUT_FILENO);
        if (dup2(all_cmd->cmds[i].fd_o, STDOUT_FILENO) == -1)
        {
            all_cmd->status = 1;
            return (errno);
        }
        close(all_cmd->cmds[i].fd_o);
    }
    return (-1);
}

int handle_redir_fork(t_cmd *cmd)
{
    if (cmd->fd_i != 0)
    {
        if (dup2(cmd->fd_i, STDIN_FILENO) == -1)
            return (errno);
        close(cmd->fd_i);
    }
    if (cmd->fd_o != 1)
    {
        cmd->saved_stdout = dup(STDOUT_FILENO);
        if (dup2(cmd->fd_o, STDOUT_FILENO) == -1)
            return (errno);
        close(cmd->fd_o);
    }
    return (-1);
}