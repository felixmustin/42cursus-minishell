/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:52:58 by fmustin           #+#    #+#             */
/*   Updated: 2021/10/04 16:42:37 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_length;
	size_t	src_length;

	src_length = ft_strlen(src);
	dst_length = ft_strlen(dst);
	i = 0;
	j = dst_length;
	if (size > 0 && dst_length < size - 1)
	{
		while (src[i] && dst_length < size - 1 - i)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = 0;
	}
	if (dst_length >= size)
		return (size + src_length);
	return (dst_length + src_length);
}
