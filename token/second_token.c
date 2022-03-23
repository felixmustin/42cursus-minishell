#include "../minishell.h"

char	*new_content(t_list **lst)
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

char	*new_content_varaible(t_list **lst)
{
	t_token_type	type;
	char			*content;
	char			*tpm;
	char			*tpm1;
	
	type = variable;
	content = ft_strdup((*lst)->token->content);
	*lst = (*lst)->next;
	while (*lst && (*lst)->token->type != space)
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

t_token_type	check_double(char *content, t_token_type type)
{
	if (content[0] == '>' && content[1] == '>')
		type = double_redir_right;
	if (content[0] == '<' && content[1] == '<')
		type = double_redir_left;
	if (content[0] == '|' && content[1] == '|')
		type = or;
	if (content[0] == '&' && content[1] == '&')
		type = and;
	return (type);
}

int	set_second_token(t_list **lst, t_list **newlist)
{
	char			*content;
	t_token			*token;
	t_list			*new;
	t_token_type	type;

	type = (*lst)->token->type;
	if (type == variable)
		content = new_content_varaible(lst);
	else
		content = new_content(lst);
	type = check_double(content, type);
	token = create_token(content, type);
	new = newlst(token);
	add_back(newlist, new);
	return (1);
}

int	second_token(t_list **lst)
{
	t_list	*new;
	int		i;

	i = 0;
	new = NULL;
	while (*lst)
	{
		/*if (i == 0)
			i = set_second_token(lst, &new);
		if (i > 0)
			i--;*/
		set_second_token(lst, &new);
		//if (*lst)
		//	*lst = (*lst)->next;
	}
	//free lst
	*lst = first_lst(new);
	return (1);
}