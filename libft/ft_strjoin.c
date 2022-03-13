/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 13:38:47 by fmustin           #+#    #+#             */
/*   Updated: 2021/10/08 13:40:10 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	total_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1) + 1;
	total_len = ft_strlen(s2) + s1_len;
	new_str = malloc(total_len * sizeof(char));
	if (!new_str)
		return (0);
	ft_strlcpy(new_str, s1, s1_len);
	ft_strlcat(new_str, s2, total_len);
	return (new_str);
}
