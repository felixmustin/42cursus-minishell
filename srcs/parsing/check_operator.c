#include "../../includes/minishell.h"

int close_op(char **input, char *content)
{
    char *tmp;

    tmp = ft_strdup(*input);
	free(*input);
	*input = NULL;
	*input = ft_strjoin(tmp, content);
    if (!*input)
        return (0);
    free(tmp);
    return (1);
}

int check_closed_op(char *line)
{
	int i;
	int val;

	i = 0;
	val = 0;
    while(line[i])   
	{
		if (line[i] >= 33 && line[i] <= 126)
			val = 1;
		i++;
	}
	return (val);
}

int unclosed_operator(char **input)
{
	char *content;
	char *tmp;
	char *line;

	content = ft_strdup("\n");
	ft_putstr("pipe>");
    line = get_next_line(0);
    while(line)
    {
		if (get_sig_code())
            return (0);
		tmp = ft_strdup(content);
		ft_free(content);
		content = ft_strjoin(tmp, line);
		ft_free(tmp);
		tmp = NULL;
        if (check_closed_op(line))
        	return (close_op(input, content));
		ft_putstr("pipe>");
        ft_free(line);
        line = get_next_line(0);
    }
    ft_free(line);
	return(close_op(input, content));
}