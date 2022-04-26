#include "../../includes/minishell.h"

void	init_struct(t_cmd *cmd)
{
	cmd->fd_i = 0;
	cmd->fd_o = 1;
	cmd->pipe_i = 0;
	cmd->pipe_o = 0;
	cmd->type = -1;
	cmd->f_redir = 0;
}

int	count_cmd(t_lists *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->token->type == pipeline)
			i++;
		lst = lst->next;
	}
	return (i + 1);
}

int get_type(char **str)
{
    if (ft_strlen(str[0]) == 4 && !ft_strncmp(str[0], "echo", 4))
        return (1);
    else if (ft_strlen(str[0]) == 2 && !ft_strncmp(str[0], "cd", 2))
        return (2);
    else if (ft_strlen(str[0]) == 3 && !ft_strncmp(str[0], "pwd", 3))
        return (3);
    else if (ft_strlen(str[0]) == 6 && !ft_strncmp(str[0], "export", 6))
        return (4);
    else if (ft_strlen(str[0]) == 5 && !ft_strncmp(str[0], "unset", 5))
        return (5);
    else if (ft_strlen(str[0]) == 3 && !ft_strncmp(str[0], "env", 3))
        return (6);
    else if (ft_strlen(str[0]) == 4 && !ft_strncmp(str[0], "exit", 4))
        return (7);
    else
        return (0);
}

int	print_syntax_error(char *str, int i)
{
	if (ft_strncmp(str, "\n", 1) == 0)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token `%c'\n", str[i]);
	return (0);
}

void	ft_free(char *str)
{
	free(str);
	str = NULL;
}
