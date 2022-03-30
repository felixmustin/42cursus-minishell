#include "../minishell.h"

int	single_token(t_list *lst)
{
	int				i;
	t_token_type	type;

	i = 0;
	type = lst->token->type;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	if (i == 1)
		if (type != literal || type != double_redir_left || type != double_redir_right || type != simple_redir_left || type != simple_redir_right)
			return (0);
	return (1);
}

int	parsing(t_all_cmd *all_cmd, t_list *lst)
{
	if (!check_quotes(lst))
		return (0);
	if (!check_operator(lst))
		return (0);
	if (!single_token(lst))
		return (0);
	if (!parse_command(lst))
		return (0);
	if (set_cmd(all_cmd, lst))
	return (1);
}