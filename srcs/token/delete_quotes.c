/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmillet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:21:35 by cmillet           #+#    #+#             */
/*   Updated: 2022/04/26 12:21:38 by cmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*split_to_str(char **split)
{
	char	*str;
	char	*tpm;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (split[i] != NULL)
	{
		tpm = ft_strdup(str);
		free(str);
		str = NULL;
		str = ft_strjoin(tpm, split[i]);
		free(tpm);
		tpm = NULL;
		i++;
	}
	return (str);
}

int	check_empty_quotes(t_lists *lst)
{
	t_lists	*prev;
	t_lists	*next;

	prev = lst->prev;
	next = lst->next;
	if (next)
	{
		if (next->token->type != space)
			return (0);
	}
	if (prev)
	{
		if (prev->token->type != space)
			return (0);
	}
	return (1);
}

int	delete_double_quotes(t_lists **lst)
{
	char	**split;

	if (ft_strlen((*lst)->token->content) == 2)
	{
		if (check_empty_quotes(*lst))
		{
			free((*lst)->token->content);
			(*lst)->token->content = set_split(-2);
		}
		else
			(*lst)->token->type = undesirable;
		return (0);
	}
	split = ft_split((*lst)->token->content, 34);
	free((*lst)->token->content);
	(*lst)->token->content = NULL;
	(*lst)->token->content = split_to_str(split);
	free_env(split);
	return (0);
}

int	delete_single_quotes(t_lists **lst)
{
	char	**split;

	if (ft_strlen((*lst)->token->content) == 2)
	{
		if (check_empty_quotes(*lst))
		{
			free((*lst)->token->content);
			(*lst)->token->content = set_split(-2);
		}
		else
			(*lst)->token->type = undesirable;
		return (0);
	}
	split = ft_split((*lst)->token->content, 39);
	free((*lst)->token->content);
	(*lst)->token->content = NULL;
	(*lst)->token->content = split_to_str(split);
	free_env(split);
	return (0);
}

int	delete_quotes(t_lists **lst)
{
	t_lists	*tpm;

	tpm = *lst;
	while (*lst)
	{
		if ((*lst)->token->type == double_quote)
			delete_double_quotes(lst);
		if ((*lst)->token->type == single_quote)
			delete_single_quotes(lst);
		*lst = (*lst)->next;
	}
	*lst = tpm;
	return (0);
}
