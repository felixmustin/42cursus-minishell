/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:36:18 by fmustin           #+#    #+#             */
/*   Updated: 2021/10/08 16:45:55 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tab_count(char const *s, char c)
{
	int	i;
	int	count;
	int	tmp;

	i = 0;
	count = 0;
	tmp = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			tmp = 0;
		else if (tmp == 0)
		{
			tmp = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int	ft_tab_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char	**ft_tab_free(char const **s, int i)
{
	while (i > 0)
	{
		i--;
		free((void *)s[i]);
	}
	free(s);
	return (0);
}

static char	**create_malloc(char const *s, char c)
{
	char	**pa;

	pa = malloc(sizeof(char *) * (ft_tab_count(s, c) + 1));
	if (!pa || !s)
		return (0);
	return (pa);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**new;

	i = 0;
	j = 0;
	new = create_malloc(s, c);
	if (!new)
		return (0);
	while (s[i] != '\0' && j < ft_tab_count(s, c))
	{
		while (s[i] == c)
			i++;
		k = 0;
		new[j] = (char *)malloc(ft_tab_len(s, c, i) + 1);
		if (!(new[j]))
			return (ft_tab_free((char const **)new, j));
		while (s[i] != '\0' && s[i] != c)
			new[j][k++] = s[i++];
		new[j][k] = '\0';
		j++;
	}
	new[j] = 0;
	return (new);
}
