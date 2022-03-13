/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:58:54 by fmustin           #+#    #+#             */
/*   Updated: 2021/10/07 16:59:19 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	tot;
	void	*ptr;

	tot = count * size;
	ptr = malloc(tot);
	if (!ptr)
		return (0);
	return (ft_memset(ptr, 0, tot));
}
