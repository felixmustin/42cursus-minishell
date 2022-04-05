#include "../../includes/minishell.h"

int	main_token(char *input, t_lists **lst)
{
	if (!token(input, lst))
		return (0);
	if (!second_token(lst))
		return (0);
	if (!third_token(lst))
		return (0);
	return (1);
}