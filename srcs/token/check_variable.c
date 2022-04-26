/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmillet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:21:28 by cmillet           #+#    #+#             */
/*   Updated: 2022/04/26 12:21:30 by cmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_status(char **str)
{
	char	*tpm;
	int		i;

	i = 0;
	if (ft_strlen(*str) == 2)
	{
		if (ft_strncmp(*str, "$?", 2) == 0)
		{
			tpm = ft_itoa(get_sig_code());
			free(*str);
			*str = NULL;
			*str = ft_strdup(tpm);
			free(tpm);
			return (1);
		}
	}
	return (0);
}

int	search_variable(char **str)
{
	int		i;
	size_t	j;
	char	*tpm;

	i = 0;
	if (ft_strlen(*str) == 1)
		return (0);
	tpm = ft_substr(*str, 1, ft_strlen(*str));
	while (g_env[i] && ft_strncmp(tpm, g_env[i], ft_strlen(tpm)) != 0)
		i++;
	free(*str);
	if (!g_env[i])
	{
		*str = ft_strdup("");
		return (0);
	}
	j = 0;
	while (g_env[i][j] != '=')
		j++;
	if (j != ft_strlen(tpm))
		*str = ft_strdup("");
	else
		*str = ft_substr(g_env[i], j + 1, ft_strlen(g_env[i]));
	free(tpm);
	return (1);
}
