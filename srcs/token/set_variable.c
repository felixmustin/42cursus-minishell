/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmillet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:22:10 by cmillet           #+#    #+#             */
/*   Updated: 2022/04/26 12:22:12 by cmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fill_variable(t_lists **lst)
{
	char	*str;
	char	*tpm;
	char	*tpm1;

	str = ft_strdup((*lst)->token->content);
	*lst = (*lst)->next;
	while (*lst && (*lst)->token->type != space
		&& (*lst)->token->type != variable
		&& (*lst)->token->type != double_quote
		&& (*lst)->token->type != single_quote)
	{
		tpm = ft_strdup((*lst)->token->content);
		tpm1 = ft_strjoin(str, tpm);
		free(str);
		str = NULL;
		str = ft_strdup(tpm1);
		free(tpm);
		free(tpm1);
		tpm = NULL;
		tpm1 = NULL;
		*lst = (*lst)->next;
	}
	return (str);
}

int	set_content(t_lists **lst, t_lists **newlist)
{
	t_token			*token;
	char			*content;
	t_token_type	type;
	t_lists			*new;

	type = (*lst)->token->type;
	if (type == variable)
		content = fill_variable(lst);
	else
	{
		content = ft_strdup((*lst)->token->content);
		*lst = (*lst)->next;
	}
	token = create_token(content, type);
	new = newlst(token);
	add_back(newlist, new);
	return (0);
}

int	set_variable(t_lists **lst)
{
	t_lists	*new;
	t_lists	*tmp;

	new = NULL;
	tmp = *lst;
	while (*lst)
		set_content(lst, &new);
	*lst = tmp;
	free_lst(lst);
	*lst = first_lst(new);
	return (0);
}
