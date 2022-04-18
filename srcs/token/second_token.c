#include "../../includes/minishell.h"

char	*new_content(t_lists **lst)
{
	t_token_type	type;
	char			*content;
	char			*tpm;
	char			*tpm1;

	type = (*lst)->token->type;
	content = ft_strdup((*lst)->token->content);
	*lst = (*lst)->next;
	while (*lst && type == (*lst)->token->type)
	{
		tpm = ft_strdup((*lst)->token->content);
		tpm1 = ft_strjoin(content, tpm);
		free(content);
		content = NULL;
		content = ft_strdup(tpm1);
		free(tpm1);
		free(tpm);
		tpm1 = NULL;
		tpm = NULL;  
		*lst = (*lst)->next;
	}
	return (content);
}

char	*new_content_varaible(t_lists **lst)
{
	t_token_type	type;
	char			*content;
	
	type = variable;
	content = ft_strdup((*lst)->token->content);
	search_variable(&content);
	*lst = (*lst)->next;
	return (content);
}

char	*new_content_quotes(t_lists **lst, t_token_type type)
{
	char	*content;
	char	*tpm;
	char	*tpm1;
	int		quotes;

	content = ft_strdup((*lst)->token->content);
	*lst = (*lst)->next;
	quotes = 0;
	while (*lst && !quotes)
	{
		tpm = ft_strdup((*lst)->token->content);
		if (type == double_quote && (*lst)->token->type == variable)
			search_variable(&tpm);
		tpm1 = ft_strjoin(content, tpm);
		free(content);
		content = NULL;
		content = ft_strdup(tpm1);
		free(tpm1);
		tpm1 = NULL;
		free(tpm);
		tpm = NULL;
		if ((*lst)->token->type == type)
			quotes = 1;
		*lst = (*lst)->next;
	}
	return (content);
}

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

int	set_second_token(t_lists **lst, t_lists **newlist)
{
	char			*content;
	t_token			*token;
	t_lists			*new;
	t_token_type	type;

	type = (*lst)->token->type;
	if (type == variable)
		content = new_content_varaible(lst);
	if (type == single_quote || type == double_quote)
		content = new_content_quotes(lst, type);
	if (type != variable && type != double_quote && type != single_quote)
		content = new_content(lst);
	type = check_double(content, type);
	token = create_token(content, type);
	new = newlst(token);
	add_back(newlist, new);
	return (1);
}

int	second_token(t_lists **lst)
{
	t_lists	*new;

	new = NULL;
	while (*lst)
		set_second_token(lst, &new);
	*lst = first_lst(new);
	return (1);
}