#include "../minishell.h"

int	check_lst(t_list *lst)
{
	t_token_type	*next;
	t_token_type	*prev;

	prev = lst->prev->token->type;
	next = lst->next->token->type;
	if ((prev != literal || prev != double_redir_left || prev != double_redir_right || prev != simple_redir_left || prev != simple_redir_right) && (next != literal || next != double_redir_left || next != double_redir_right || next != simple_redir_right || next != simple_redir_left))
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