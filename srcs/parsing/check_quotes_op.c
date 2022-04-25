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

int	check_redir(char *str, int i)
{
	int	count;
	int	space;
	int	j;

	count = 0;
	j = i;
	space = 0;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == str[j]))
	{
		if (str[i] == str[j])
		{
			count++;
			if (count > 1 && space > 0)
				count = 3;
		}
		if (str[i] == 32)
			space++;
		i++;
	}
	if (count > 2)
	{
		print_syntax_error(str, j);
		return (0);
	}
	if (str[i] == '\0' || str[i] == '#' || str[i] == '&' || str[i] == '|' || str[i] == ')' || str[i] == ')')
	{
		if (str[i] == '\0' || str[i] == '#')
			print_syntax_error("\n", 0);
		else
			print_syntax_error(str, i);
		return (0);
	}
	if (str[i] == '*')
	{
		printf("bash ambiguous redirect\n");
		return (0);
	}
	return (1);
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
		if ((*str)[i] == 62 || (*str)[i] == 60)
		{
			if (!check_redir(*str, i))
				return (0);
		}
		i++;
	}
	return (1);
}