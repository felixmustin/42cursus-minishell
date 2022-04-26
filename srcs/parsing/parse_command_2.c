/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:42:07 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 14:44:46 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_env(char *str)
{
	if (ft_strlen(str) > 3)
	{
		if (str[0] == 'P')
			if (str[1] == 'A')
				if (str[2] == 'T')
					if (str[3] == 'H')
						return (1);
	}
	return (0);
}

int	check_acces(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (access(str[i], F_OK) != -1 && access(str[i], X_OK) != -1)
			return (i);
		i++;
	}
	return (-1);
}
