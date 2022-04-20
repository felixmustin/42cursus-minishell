#include "../../includes/minishell.h"

int	check_quote_occurence(char *str, int i)
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


int	check_operator(char **str, int i)
{
	int	j;
	int val;

	val = 0;
	j = i;
	while (--j > 0 && (*str)[j] != 124)
	{
		if ((*str)[j] >= 33 && (*str)[j] <= 126)
			val = 1;
	}
	if (val == 0)
		return(print_syntax_error(*str, i));
	val = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] >= 33 && (*str)[i] <= 126 && (*str)[i] != 124)
			val = 1;
		if ((*str)[i] == 124)
			return(check_operator(str, i));
	}
	if (val == 0)
		return (1);
	return (2);
}

int check_quotes_op(char **str)
{
	int i;
	int ret;

	i = 0;
	while((*str)[i])
	{
		if ((*str)[i] == 34 || (*str)[i] == 39)
		{
			i = check_quote_occurence(*str, i);
			if (i == -1)
				return (unclosed_quotes(str));
		}
		if ((*str)[i] == 124)
		{
			ret = check_operator(str, i);
			if (ret == 0)
				return(0);
			if (ret == 1)
				if(!unclosed_operator(str))
					return(0);
		}
		i++;
	}
	return (1);
}