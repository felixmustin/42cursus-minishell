#include "../minishell.h"

t_list	*newlst(t_token *token)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->token = token;
	new->next = NULL;
	return (new);
}

t_list	*last_lst(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	add_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst)
	{
		last = last_lst(*lst);
		last->next = new;
	}
	else
		*lst = new;
}