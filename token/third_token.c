#include "../minishell.h"

char	*new_content_literal(t_list **lst, t_token_type type)
{
	char			*content;
	char			*tpm;
	char			*tpm1;

	content = ft_strdup((*lst)->token->content);
	*lst = (*lst)->next;
	while (*lst && ((*lst)->token->type == literal || (*lst)->token->type == space || (*lst)->token->type == variable))
	{
		tpm = ft_strdup((*lst)->token->content);
		tpm1 = ft_strjoin(content, tpm);
		free(content);
		content = NULL;
		content = ft_strdup(tpm1);
		free(tpm);
		free(tpm1);
		tpm = NULL;
		tpm1 = NULL;
		*lst = (*lst)->next;
	}
	return (content);
}

char	*new_content_redir(t_list **lst)
{
	char	*content;
	char	*tpm;
	char	*tpm1;

	content = NULL;
	while ((*lst)->token->type != literal && lst)
		*lst = (*lst)->next;
	if (lst)
		content = ft_strdup((*lst)->token->content);
	*lst = (*lst)->next;
	while (*lst && (*lst)->token->type == literal)
	{
		tpm = ft_strdup((*lst)->token->content);
		tpm1 = ft_strjoin(content, tpm);
		free(content);
		content = NULL;
		content = ft_strdup(tpm1);
		free(tpm);
		free(tpm1);
		tpm = NULL;
		tpm1 = NULL;
		*lst = (*lst)->next;
	}
	return (content);
}

char	*neww_content(t_list **lst, t_token_type type)
{
	char	*content;
	char	*tpm;
	char	*tpm1;

	content = ft_strdup((*lst)->token->content);
	*lst = (*lst)->next;
	while (*lst && type == (*lst)->token->type)
	{
		tpm = ft_strdup((*lst)->token->content);
		tpm1 = ft_strjoin(content, tpm);
		free(content);
		content = NULL;
		content = tpm1;
		free(tpm1);
		free(tpm);
		tpm1 = NULL;
		tpm = NULL;
		*lst = (*lst)->next;
	}
	return (content);
}

int	set_third_token(t_list **lst, t_list **newlist)
{
	char			*content;
	t_token			*token;
	t_token_type	type;
	t_list			*new;

	type = (*lst)->token->type;
	if (type != space)
	{
		if (type == literal || type == variable)
		{
			content = new_content_literal(lst, type);
			token = create_token(content, type);
			new = newlst(token);
			add_back(newlist, new);
			return (1);
		}
		if (type == simple_redir_left || type == simple_redir_right || type == double_redir_left || type == double_redir_right)
		{
			content = new_content_redir(lst);
			token = create_token(content, type);
			new = newlst(token);
			add_back(newlist, new);
			return (1);
		}
		else
			content = neww_content(lst, type);
		token = create_token(content, type);
		new = newlst(token);
		add_back(newlist, new);
	}
	if (type == space)
		*lst = (*lst)->next;
	return (1);
}

int third_token(t_list **lst)
{
	t_list	*new;

	new = NULL;
	while (*lst)
	{
		set_third_token(lst, &new);
	}
	//free lst
	*lst = first_lst(new);
	return (1);
}