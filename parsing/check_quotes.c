#include "../minishell.h"

/*int	check_second_quotes(char *str, int i, int nbr)
{
	int	j;

	j = i + 1;
	while (str[j] != '\0')
	{
		if (str[j] == nbr)
			return (1);
		j++;
	}
	return (0);
}

int	check_quotes(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->token->type == literal)
		{
			while (lst->token->content[i] != '\0')
			{
				if (lst->token->content[i] == 47)
					if (!check_second_quotes(lst->token->content, i, 47))
						return (0);
				if (lst->token->content[i] == 42)
					if (!check_second_quotes(lst->token->content, i, 47))
						return (0);
			}
		}
	}
}*/

int	check_occurence(char *str, int i, int j)
{
	while (j > i)
	{
		if (str[i] == str[j])
			return (-1);
		j--;
	}
	return (j);
}

int	check_str(char	*str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	while (str[i] != '\0')
	{
		if (j > i && (str[i] == 42 || str[i] == 47))
		{
			j = check_occurence(str, i , j);
			if (j = -1)
				return (0);
			else
				j--;
		}
		i++;
	}
	return (0);
}

int	check_quotes(t_list *lst)
{
	while (lst)
	{
		if (check_str(lst->token->type == literal))
			if (!check_str(lst->token->content))
				return (0);
		lst = lst->next;
	}
	return (1);
}