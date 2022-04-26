/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:22 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 12:07:23 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_cwd_2(char **mid_cwd)
{
	char	*home;
	char	*last_cwd;

	home = ft_strjoin("\U0001F449 ", *mid_cwd);
	last_cwd = ft_strjoin(home, DEFAULT);
	free(home);
	free(*mid_cwd);
	return (last_cwd);
}

char	*parse_cwd(char *cwd)
{
	char	*cut_cwd;
	char	*mid_cwd;
	int		i;
	int		j;

	i = ft_strlen(cwd);
	j = i;
	while (cwd[i] != '/')
		i--;
	cut_cwd = malloc(sizeof(char) * (j - i) + 1);
	if (!cut_cwd)
		return (NULL);
	j = 0;
	while (cwd[++i])
		cut_cwd[j++] = cwd[i];
	cut_cwd[j++] = ' ';
	cut_cwd[j] = 0;
	mid_cwd = ft_strjoin(RED, cut_cwd);
	free(cut_cwd);
	return (parse_cwd_2(&mid_cwd));
}

char	*new_prompt(void)
{
	char	*cwd;
	char	*last_cwd;

	cwd = getcwd(NULL, 0);
	last_cwd = parse_cwd(cwd);
	free(cwd);
	return (last_cwd);
}
