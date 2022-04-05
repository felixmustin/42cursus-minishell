#include "../../includes/minishell.h"

void	free_content(t_lists *lst)
{
	while (lst)
	{
		if (lst->token)
			if (lst->token->content)
				free(lst->token->content);
		lst = lst->next;
	}
}

void	free_token(t_lists *lst)
{
	while (lst)
	{
		if (lst->token)
			free(lst->token);
		lst = lst->next;
	}
}

void	free_lst(t_lists **lst)
{
	free_content(*lst);
	free_token(*lst);
	while (*lst)
	{
		free(*lst);
		*lst = (*lst)->next;
	}
	*lst = NULL;
}