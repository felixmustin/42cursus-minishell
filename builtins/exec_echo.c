#include "../minishell.h"

void ex_echo(t_cmd *cmd)
{
    int i;

    i = 1;
    if (ft_strncmp(cmd->cmd[1], "-n", 2) == 0)
    {
        while (cmd->cmd[++i])
            ft_putstr(cmd->cmd[i]);
    }
    else
    {
        i--;
        while (cmd->cmd[++i])
            ft_putstr(cmd->cmd[i]);
        ft_putstr("\n");
    }
}