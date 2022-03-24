#include "../minishell.h"

int	single_token(t_list *lst)
{
	int		i;
	t_list	*first;

	i = 0;
	first = lst;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	if (i == 1)
		if (first->token->type != literal)
			return (0);
	return (1);
}

int	parsing(t_list *lst)
{
	if (!check_quotes(lst))
		return (0);
	if (!check_operator(lst))
		return (0);
	if (!single_token(lst))
		return (0);
	return (1);
}