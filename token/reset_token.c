#include "../minishell.h"

char	*new_content(t_list *lst)
{
	t_token_type	type;
	char			*content;
	char			*tpm;
	char			*tpm1;

	type = lst->token->type;
	content = ft_strdup(lst->token->content);
	lst = lst->next;
	while (type == lst->token->type && lst)
	{
		tpm = ft_strdup(lst->token->content);
		tpm1 = ft_strdup(content);
		free(content);
		content = NULL;
		content = ft_strjoin(tpm1, tpm);
		lst = lst->next;
	}
	return (content);
}

int	reset_token(t_list **lst, t_list **newlist)
{
	char			*content;
	t_token			*token;
	t_list			*new;
	t_token_type	type;

	content = new_content(*lst);
	type = (*lst)->token->type;
	token = create_token(content, type);
	new = newlst(token);
	add_back(newlist, new);
	return (ft_strlen(content));
}

int	final_token(t_list **lst)
{
	t_list	*new;
	int		i;

	i = 0;
	while (*lst)
	{
		if (i = 0)
			i = reset_token(lst, &new);
		if (i > 0)
			i--;
		*lst = (*lst)->next;
	}
	*lst = new;
}