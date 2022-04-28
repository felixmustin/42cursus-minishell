/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:05:39 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 12:05:42 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_echo_2(t_all_cmd *all_cmd, int i, int j)
{
	while (all_cmd->cmds[j].cmd[++i])
	{		
		ft_putstr(all_cmd->cmds[j].cmd[i]);
		if (all_cmd->cmds[j].cmd[i + 1])
			ft_putstr(" ");
	}
	ft_putstr("\n");
}

void	ex_echo(t_all_cmd *all_cmd, int j)
{
	int	i;

	i = 1;
	if (all_cmd->cmds[j].cmd[1])
	{
		if (ft_strncmp(all_cmd->cmds[j].cmd[1], "-n", 2) == 0)
		{
			while (all_cmd->cmds[j].cmd[++i])
			{
				ft_putstr(all_cmd->cmds[j].cmd[i]);
				if (all_cmd->cmds[j].cmd[i + 1])
					ft_putstr(" ");
			}
		}
		else
			exec_echo_2(all_cmd, i - 1, j);
	}
	else
		ft_putstr("\n");
	all_cmd->status = 0;
	return ;
}
