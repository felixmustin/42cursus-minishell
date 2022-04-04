/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:50:38 by fmustin           #+#    #+#             */
/*   Updated: 2021/10/21 15:52:12 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	find_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_line(char **text)
{
	char	*tmp;
	char	*line;

	if (find_nl(*text) == -1)
	{
		line = ft_substr(*text, 0, ft_strlen(*text));
		free(*text);
		*text = NULL;
	}
	else
	{
		line = ft_substr(*text, 0, find_nl(*text) + 1);
		tmp = ft_substr(*text, find_nl(*text) + 1, ft_strlen(*text));
		free(*text);
		*text = NULL;
		*text = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
	}
	return (line);
}

char	*read_text(char **text, char *buffer, int fd)
{
	int		ret;
	char	*tmp;

	if (find_nl(*text) != -1)
		return (get_line(text));
	ret = read(fd, buffer, BUFFER_SIZE);
	buffer[ret] = '\0';
	if (ret <= 0)
	{
		if (**text)
			return (get_line(text));
		else
		{
			free(*text);
			*text = NULL;
			return (0);
		}
	}
	tmp = ft_strjoin(*text, buffer);
	free(*text);
	*text = NULL;
	*text = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (read_text(text, buffer, fd));
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*text;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	if (!text)
		text = ft_strdup("");
	line = read_text(&text, buffer, fd);
	free(buffer);
	buffer = NULL;
	return (line);
}
