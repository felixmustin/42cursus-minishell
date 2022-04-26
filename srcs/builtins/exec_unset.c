/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:06:19 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 12:06:20 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_env_suppr(char *str, char **tmp_env)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(str);
	j = -1;
	i = 0;
	while (tmp_env[++j])
	{
		if (ft_strncmp(tmp_env[j], str, len) != 0)
			i++;
	}
	env = malloc(sizeof(char *) * (env_len(tmp_env) + i));
	i = -1;
	j = -1;
	while (tmp_env[++i])
	{
		if (ft_strncmp(tmp_env[i], str, len) != 0)
			env[++j] = ft_strdup(tmp_env[i]);
	}
	env[++j] = 0;
}

int	check_if_vals(char *str)
{
	int	i;

	i = 0;
	if (str[i] < 65 || str[i] > 122)
		return (0);
	while (str[i] >= 65 && str[i] <= 122)
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	print_error_unset(t_all_cmd *all_cmd, int j, int i)
{
	char	*str;
	char	*str2;

	all_cmd->status = 1;
	str = ft_strjoin("minishell: unset: ", all_cmd->cmds[j].cmd[i]);
	str2 = ft_strjoin(str, " not a valid identifier\n");
	ft_putstr_fd(str2, STDERR_FILENO);
	free(str);
	free(str2);
}

int	check_valid(t_all_cmd *all_cmd, int j)
{
	char	*str;
	char	*str2;

	if (all_cmd->cmds[j].cmd[1])
	{
		if (all_cmd->cmds[j].cmd[1][0] == '-')
		{
			all_cmd->status = 2;
			str = ft_strjoin("minishell: unset: ", all_cmd->cmds[j].cmd[1]);
			str2 = ft_strjoin(str, " invalid option\n");
			ft_putstr_fd(str2, STDERR_FILENO);
			free(str);
			free(str2);
			return (1);
		}
	}
	return (0);
}

void	ex_unset(t_all_cmd *all_cmd, int j)
{
	char	**tmp_env;
	int		i;

	if (check_valid(all_cmd, j))
		return ;
	i = 1;
	while (all_cmd->cmds[j].cmd[i])
	{
		if (check_if_vals(all_cmd->cmds[j].cmd[i]))
		{
			tmp_env = dup_env();
			free_env(env);
			init_env_suppr(all_cmd->cmds[j].cmd[i], tmp_env);
			free_env(tmp_env);
		}
		else
			print_error_unset(all_cmd, j, i);
		i++;
	}
}
