/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:05:52 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 12:05:53 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ex_env(t_all_cmd *all_cmd, int j)
{
	int	i;

	if (all_cmd->cmds[j].cmd[1])
	{
		all_cmd->status = 1;
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		return ;
	}
	i = 0;
	while (g_env[++i])
	{
		ft_putstr(g_env[i]);
		ft_putstr("\n");
	}
}
