#include "../minishell.h"

void init_struct(t_cmd *cmd)
{
    cmd->pipe_i = 0;
    cmd->pipe_o = 0;
    cmd->and_i = 0;
    cmd->and_o = 0;
    cmd->or_i = 0;
    cmd->or_o = 0;
}