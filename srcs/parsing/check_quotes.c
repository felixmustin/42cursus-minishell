/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:53:35 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 14:59:32 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quote_occurence(char *str, int i)
{
	int	j;

	j = i + 1;
	while (str[j] != '\0')
	{
		if (str[j] == str[i])
			return (j);
		j++;
	}
	return (-1);
}

int	close_quotes(char **input, char *content, char *line, int i)
{
	char	*tmp;

	if (i == 1)
	{
		tmp = ft_strdup(*input);
		ft_free(*input);
		*input = ft_strjoin(tmp, content);
		if (!*input)
			return (0);
		free(tmp);
	}
	free(content);
	free(line);
	if (i == 0)
		return (0);
	return (1);
}

int	check_closed_quote(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34 || line[i] == 39)
			count++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

int	unclosed_quotes(char **input)
{
	char	*content;
	char	*tmp;
	char	*line;

	input_signals();
	set_sig_code(0);
	content = ft_strdup("\n");
	ft_putstr("quote>");
	line = get_next_line(0);
	while (line)
	{
		if (get_sig_code())
			return (close_quotes(input, content, line, 0));
		tmp = ft_strdup(content);
		ft_free(content);
		content = ft_strjoin(tmp, line);
		ft_free(tmp);
		if (check_closed_quote(line))
			return (close_quotes(input, content, line, 1));
		ft_putstr("quote>");
		ft_free(line);
		line = get_next_line(0);
	}
	return (close_quotes(input, content, line, 1));
}
