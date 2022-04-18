#include "../../includes/minishell.h"

void ex_env(t_all_cmd *all_cmd, int j)
{
    int i;

    if (all_cmd->cmds[j].cmd[1])
    {
        all_cmd->status = 1;
        ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
        return ;
    }
    i = 0;
    while(env[++i])
    {
        ft_putstr(env[i]);
        ft_putstr("\n");
    }
}