#include "../minishell.h"

char	*set_value(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_token_type	define_type(char c)
{
	t_token_type	type;

	type = literal;
	if (c == '&')
		type = and;
	if (c == '|')
		type = pipeline;
	if (c == '>')
		type = simple_redir_right;
	if (c == '<')
		type = simple_redir_left;
	if (c == '$')
		type = variable;
	if (c == ' ' || c == '\f' || c == '\n' || c == '\v' || c == '\t' || c == '\r')
		type = space;
	if (c == 42)
		type = double_quote;
	if (c == 47)
		type = single_quote;
	return (type);
}

t_token	*create_token(char *content, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
	token->type = type;
	return (token);
}

int	set_token(char c, t_lists **lst)
{
	char			*content;
	t_lists			*new;
	t_token			*token;
	t_token_type	type;

	content = set_value(c);
	if (!content)
		return (0);
	type = define_type(c);
	token = create_token(content, type);
	new = newlst(token);
	if (!new)
		return (0);
	add_back(lst, new);
	return (1);
}

int	token(char *input, t_lists **lst)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (!set_token(input[i], lst))
			return (0);
		i++;
	}
	return (1);
}