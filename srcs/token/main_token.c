#include "../../includes/minishell.h"

int	main_token(char *input, t_lists **lst, int status)
{
	if (!token(input, lst))
		return (0);
	set_variable(lst);
	if (!second_token(lst, status))
		return (0);
	delete_quotes(lst);
	//check_variable(lst);
	if (!third_token(lst))
		return (0);
	return (1);
}