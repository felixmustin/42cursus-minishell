/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:40:18 by fmustin           #+#    #+#             */
/*   Updated: 2021/10/08 16:51:43 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*liste;
	t_list	*new;

	if (!lst || !f)
		return (0);
	liste = malloc(sizeof(t_list));
	if (!liste)
		return (0);
	liste = 0;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&liste, del);
			return (0);
		}
		ft_lstadd_back(&liste, new);
		lst = lst->next;
	}
	return (liste);
}
