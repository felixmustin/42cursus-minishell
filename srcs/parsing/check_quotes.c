#include "../../includes/minishell.h"

int	check_occurence(char *str, int i)
{
	int	j;

	j = i + 1;
	while (str[j] != '\0')
	{
		if (str[j] == str[i])
			return (j);
		j++;
	}
	return (-1);
}

int	check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i = check_occurence(str, i);
			if (i == -1)
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_quotes(char *input)
{
	if (!check_str(input))
		return (0);
	return (1);
}