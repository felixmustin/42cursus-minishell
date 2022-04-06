#include "../../includes/minishell.h"

int	check_occurence(char *str, int i, int j)
{
	while (j > i)
	{
		if (str[j] == str[i])
			return (j);
		j--;
	}
	return (-1);
}

int	check_str(char	*str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	while (str[i] != '\0')
	{
		if (j > i && (str[i] == 34 || str[i] == 39))
		{
			j = check_occurence(str, i , j);
			if (j == -1)
				return (0);
			else
				j--;
		}
		i++;
	}
	return (1);
}

int	check_quotes(t_lists *lst)
{
	while (lst)
	{
		if (lst->token->type == literal)
			if (!check_str(lst->token->content))
				return (0);
		lst = lst->next;
	}
	return (1);
}