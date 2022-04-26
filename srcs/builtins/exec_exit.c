/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:05:58 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 12:05:59 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_atoi(int nb, int signe)
{
	if (signe == 1)
	{
		while (nb > 255)
			nb -= 256;
	}
	else
	{
		nb *= signe;
		while (nb < 0)
			nb += 256;
	}
	return (nb);
}

int	ft_atoi_dif(const char *str)
{
	int					signe;
	unsigned long int	nb;
	unsigned long int	new;

	signe = 1;
	nb = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 43 || *str == 45 || (*str >= 48 && *str <= 57))
	{
		if (*str == 45)
			signe = -1;
	}
	else
		return (0);
	if (!(*str >= 48 && *str <= 57))
		str++;
	while (*str >= 48 && *str <= 57 && *str != '\0')
		nb = nb * 10 + (*str++ - '0');
	new = check_atoi(nb, signe);
	return (new);
}

void	exit_with_free(t_all_cmd *all_cmd, int val)
{
	if (all_cmd->nbrcmd > 1)
		free(all_cmd->pids);
	free_env(env);
	free_cmds(all_cmd);
	exit(val);
}

void	check_valid_exit(t_all_cmd *all_cmd, int i, int j)
{
	if (!ft_isdigit(all_cmd->cmds[i].cmd[1][j]))
	{
		all_cmd->status = 255;
		printf("minishell: exit: %s: numeric argument required\n",
			all_cmd->cmds[i].cmd[1]);
		exit_with_free(all_cmd, 255);
	}
}

void	ex_exit(t_all_cmd *all_cmd, int i)
{
	int	j;

	printf("exit\n");
	if (all_cmd->cmds[i].cmd[1])
	{
		j = 0;
		while (all_cmd->cmds[i].cmd[1][++j])
			check_valid_exit(all_cmd, i, j);
		if (all_cmd->cmds[i].cmd[2])
		{
			all_cmd->status = 1;
			printf("minishell: exit: too many arguments\n");
		}
		else
			exit_with_free(all_cmd, ft_atoi_dif(all_cmd->cmds[i].cmd[1]));
	}
	else
		exit_with_free(all_cmd, 0);
}
