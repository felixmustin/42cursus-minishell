#include "../minishell.h"

int	check_files(char *str)
{
	char	*files;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 32)
		{
			i++;
			files = ft_substr(str, i, ft_strlen(str));
			if (acces(files, F_OK) == -1)
				return (0);
		}
		i++;
	}
	return (1);
}

int	parse_command(t_list *lst)
{
	while (lst)
	{
		if (lst->token->type == literal)
			if (!check_files(lst->token->content))
				return (0);
	}
	return (1);
}