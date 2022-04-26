#include "../../includes/minishell.h"

int close_quotes(char **input, char *content)
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

int check_closed_quote(char *line)
{
    int count;
    int i;

    count = 0;
    i = -1;
    while (line[++i])
    {
		if (line[i] == 34 || line[i] == 39)
            count++;
	}
    if (count % 2 == 0)
        return (0);
    else
        return (1);
}

int unclosed_quotes(char **input)
{
	char *content;
	char *tmp;
	char *line;

    input_signals();
    set_sig_code(0);
	content = ft_strdup("\n");
	ft_putstr("quote>");
    line = get_next_line(0);
    while(line)
    {
        if (get_sig_code())
            return (0);
		tmp = ft_strdup(content);
        ft_free(content);
		content = ft_strjoin(tmp, line);
        ft_free(tmp);
        if (check_closed_quote(line))
            return (close_quotes(input, content));
		ft_putstr("quote>");
        ft_free(line);
        line = get_next_line(0);
    }
    ft_free(line);
	return(close_quotes(input, content));
}