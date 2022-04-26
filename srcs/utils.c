/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:27 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 12:07:28 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

static int	sig_code_static(int err_code, bool set_err_code)
{
	static int	static_err_code = 0;

	if (set_err_code)
		static_err_code = err_code;
	return (static_err_code);
}

void	set_sig_code(int err_code)
{
	sig_code_static(err_code, true);
}

int	get_sig_code(void)
{
	return (sig_code_static(0, false));
}

void	exit_with_free(t_all_cmd *all_cmd, int val)
{
	if (!(all_cmd->nbrcmd == 1 && all_cmd->cmds[0].type > 0))
		free(all_cmd->pids);
	free_env(g_env);
	free_cmds(all_cmd);
	exit(val);
}