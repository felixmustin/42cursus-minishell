/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmillet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:21:57 by cmillet           #+#    #+#             */
/*   Updated: 2022/04/26 12:21:59 by cmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token(t_lists *lst)
{
	while (lst)
	{
		printf("content : %s\n", lst->token->content);
		lst = lst->next;
	}
}

int	main_token(char *input, t_lists **lst)
{
	if (!token(input, lst))
		return (0);
	set_variable(lst);
	if (!second_token(lst))
		return (0);
	delete_quotes(lst);
	if (!third_token(lst))
		return (0);
	return (1);
}
