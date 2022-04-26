/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:06:08 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 12:06:09 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_exp(t_all_cmd *all_cmd, int j)
{
	char	*str;
	char	*str2;

	if (all_cmd->cmds[j].cmd[1])
	{
		if (all_cmd->cmds[j].cmd[1][0] == '-')
		{
			all_cmd->status = 2;
			str = ft_strjoin("minishell: export: ", all_cmd->cmds[j].cmd[1]);
			str2 = ft_strjoin(str, " invalid option\n");
			ft_putstr_fd(str2, STDERR_FILENO);
			free(str);
			free(str2);
			return (1);
		}
	}
	return (0);
}

void	print_error(t_all_cmd *all_cmd, int j, int i)
{
	char	*str;
	char	*str2;

	all_cmd->status = 1;
	str = ft_strjoin("minishell: export: ", all_cmd->cmds[j].cmd[i]);
	str2 = ft_strjoin(str, " not a valid identifier\n");
	ft_putstr_fd(str2, STDERR_FILENO);
	free(str);
	free(str2);
}
