#include "../minishell.h"

int	check_lst(t_list *lst)
{
	t_list	*next;
	t_list	*prev;

	prev = lst->prev;
	next = lst->next;
	if (prev->token->type != literal && next->token->type != literal) //check if redir can be set after operator
		return (0);
	return (1);
}

int	check_operator(t_list *lst)
{
	while (lst)
	{
		if (lst->token->type == pipeline || lst->token->type == or || lst->token == and)
			if (!check_lst(lst))
				return (0);
		lst = lst->next;
	}
	return (1);
}