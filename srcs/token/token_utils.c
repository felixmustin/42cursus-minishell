#include "../../includes/minishell.h"

t_token_type	check_double(char *content, t_token_type type)
{
	if (ft_strlen(content) >= 2)
	{
		if (content[0] == '>' && content[1] == '>')
			type = double_redir_right;
		if (content[0] == '<' && content[1] == '<')
			type = double_redir_left;
		if (content[0] == '|' && content[1] == '|')
			type = or;
		if (content[0] == '&' && content[1] == '&')
			type = and;
	}
	return (type);
}

char	*fill_content_literal(char	*content, t_lists **lst, char *split)
{
	char	*tpm;
	char	*tpm1;

	if ((*lst)->token->type == space)
	{
		tpm = ft_strdup(content);
		free(content);
		content = ft_strjoin(tpm, split);
		free(tpm);
	}
	if ((*lst)->token->type != space)
	{
		tpm = ft_strdup((*lst)->token->content);
		tpm1 = ft_strjoin(content, tpm);
		free(content);
		content = ft_strdup(tpm1);
		free(tpm);
		free(tpm1);
	}
	return (content);
}

int	fill_content(t_lists **lst, t_lists **newlist, t_token_type type)
{
	char	*content;
	t_lists	*new;
	t_token	*token;

	if (type == 0 || type == 11 || type == 10 || type == 9)
	{
		content = new_content_literal(lst);
		type = literal;
		token = create_token(content, type);
		new = newlst(token);
		add_back(newlist, new);
		return (1);
	}
	if (type == 4 || type == 5 || type == 6 || type == 7)
	{
		content = new_content_redir(lst);
		token = create_token(content, type);
		new = newlst(token);
		add_back(newlist, new);
		return (1);
	}
	return (0);
}

char	*set_split(char c)
{
	char	*split;

	split = malloc(sizeof(char) * 2);
	if (!split)
		return (NULL);
	split[0] = c;
	split[1] = '\0';
	return (split);
}
