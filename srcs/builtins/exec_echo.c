#include "../../includes/minishell.h"

void	ex_echo(t_all_cmd *all_cmd, int j)
{
	int	i;

	i = 1;
	if (all_cmd->cmds[j].cmd[1])
	{
		if (ft_strncmp(all_cmd->cmds[j].cmd[1], "-n", 2) == 0)
		{
			while (all_cmd->cmds[j].cmd[++i])
				ft_putstr(all_cmd->cmds[j].cmd[i]);
		}
		else
		{
			i--;
			while (all_cmd->cmds[j].cmd[++i])
			{
				ft_putstr(all_cmd->cmds[j].cmd[i]);
				ft_putstr(" ");
			}
		}
	}
	ft_putstr("\n");
	all_cmd->status = 0;
	return ;
}
