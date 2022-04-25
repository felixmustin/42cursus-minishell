#include "../../includes/minishell.h"

char	*new_content_literal(t_lists **lst)
{
	char			*content;
	char			*split;

	split = set_split(-1);
	content = ft_strjoin((*lst)->token->content, split);
	*lst = (*lst)->next;
	while (*lst && ((*lst)->token->type == literal
			|| (*lst)->token->type == space
			|| (*lst)->token->type == single_quote
			|| (*lst)->token->type == double_quote
			|| (*lst)->token->type == variable))
	{
		content = fill_content_literal(content, lst, split);
		*lst = (*lst)->next;
	}
	return (content);
}

char	*new_content_redir(t_lists **lst)
{
	char	*content;

	content = NULL;
	while (*lst && (*lst)->token->type != literal
		&& (*lst)->token->type != single_quote
		&& (*lst)->token->type != double_quote)
		*lst = (*lst)->next;
	content = ft_strdup((*lst)->token->content);
	*lst = (*lst)->next;
	return (content);
}

char	*neww_content(t_lists **lst, t_token_type type)
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

void	set_third_token(t_lists **lst, t_lists **newlist)
{
	char			*content;
	t_token			*token;
	t_token_type	type;
	t_lists			*new;

	type = (*lst)->token->type;
	if (type != space && type != undesirable)
	{
		if (!fill_content(lst, newlist, type))
		{
			content = neww_content(lst, type);
			token = create_token(content, type);
			new = newlst(token);
			add_back(newlist, new);
		}
	}
	if (type == space || type == undesirable)
		*lst = (*lst)->next;
}

int	third_token(t_lists **lst)
{
	t_lists	*new;

	new = NULL;
	while (*lst)
		set_third_token(lst, &new);
	free_lst(lst);
	*lst = first_lst(new);
	return (1);
}
