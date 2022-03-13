/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:47:06 by fmustin           #+#    #+#             */
/*   Updated: 2021/10/08 13:46:11 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long n)
{
	int		size;
	long	nb;

	nb = n;
	size = 1;
	if (nb < 0)
	{
		size++;
		nb = nb * -1;
	}
	while (nb > 9)
	{
		size++;
		nb = nb / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	nb = n;
	i = ft_nbrlen(n);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	str[i--] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[i--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}
