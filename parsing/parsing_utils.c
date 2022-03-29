#include "../minishell.h"

void init_struct(t_cmd *cmd)
{
    cmd->fd_i = 0;
    cmd->fd_o = 1;
    cmd->pipe_i = 0;
    cmd->pipe_o = 0;
}