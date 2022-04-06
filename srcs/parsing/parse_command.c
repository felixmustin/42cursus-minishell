#include "../../includes/minishell.h"

int check_env(char *str)
{
	if (ft_strlen(str) > 3)
	{
		if (str[0] == 'P')
			if (str[1] == 'A')
				if (str[2] == 'T')
					if (str[3] == 'H')
						return (1);
	}
    return (0); 
}

int check_acces(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
    {
        if (access(str[i], F_OK) != -1 && access(str[i], X_OK) != -1)
            return (i);
        i++;
    }
    return (-1);
}

int set_path(char **cmd)
{
    int     i;
    char    **path;
    char    **tpm;
    char    *str;

    i = 0;
    while (env && !check_env(env[i]))
        i++;
    str = ft_substr(env[i], 5, ft_strlen(env[i]));
    tpm = ft_split(str, ':');
    i = 0;
    while (tpm[i])
        i++;
    path = malloc(sizeof(char *) * i + 1);
    i = 0;
    while (tpm[i])
    {
        path[i] = ft_strjoin(tpm[i], *cmd);
        i++;
    }
    i = check_acces(path);
    if (i == -1)
        return (0);
    free(*cmd);
    *cmd = NULL;
    *cmd = ft_strdup(path[i]);
    return (1);
}

int check_cmd(t_token *token)
{
    char    *tpm;
    char    *cmd;
    char    *str;
    int     i;

    i = 0;
    while (token->content[i] != '\0' && token->content[i] != 32)
        i++;
    tpm = ft_substr(token->content, 0, i);
    cmd = ft_strjoin("/", tpm);
    if (!set_path(&cmd))
        return (0);
    str = ft_substr(token->content, i, ft_strlen(token->content));
    free(token->content);
    token->content = NULL;
    token->content = ft_strjoin(cmd, str);
    return (1);
}

int check_content(t_token *token)
{
    int     i;
    char    *str;

    i = 0;
    while (token->content[i] != '\0' && token->content[i] != 32)
        i++;
    str = ft_substr(token->content, 0, i);
    if (access(str, F_OK) != -1 && access(str, X_OK) != -1)
    {
        free(str);
        return (0);
    }
    free(str);
    return (1);
}

int check_builtins(t_token *token)
{
    char    *str;
    int     i;
    int     r;

    i = 0;
    while (token->content[i] != '\0' && token->content[i] != 32)
        i++;
    str = ft_substr(token->content, 0, i);
    if (ft_strncmp(str, "pwd", 3) == 0)
        r = 1;
    if (ft_strncmp(str, "echo", 4) == 0)
        r = 1;
    if (ft_strncmp(str, "cd", 2) == 0)
        r = 1;
    if (ft_strncmp(str, "export", 6) == 0)
        r = 1;
    if (ft_strncmp(str, "unset", 5) == 0)
        r = 1;
    if (ft_strncmp(str, "env", 3) == 0)
        r = 1;
    if (ft_strncmp(str, "exit", 4) == 0)
        r = 1;
    if (r == 1)
    {
        free(str);
        return (0);
    }
    free(str);
    return (1);
    
}

int	find_variable(char **str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(*str);
	while(env[i] && ft_strncmp(*str, env[i], len) != 0)
		i++;
	if (!env[i])
		return (0);
	while (env[i][j] != '=')
		j++;
	free(*str);
	*str = NULL;
	*str = ft_substr(env[i], j + 1, ft_strlen(env[i]));
	return (1);
}

int	check_variable(t_token *token)
{
	char	*str;
	char	*tpm;
	int		i;

	i = 0;
	while (token->content[i] != '\0' && token->content[i] != '$')
		i++;
	if (token->content[i] == '\0')
		return (0);
	str = ft_substr(token->content, i + 1, ft_strlen(token->content));
	tpm = ft_substr(token->content, 0, i);
	if (!find_variable(&str))
	{
		free(token->content);
		token->content = NULL;
		token->content = ft_strdup(tpm);
	}
	else
	{
		free(token->content);
		token->content = NULL;
		token->content = ft_strjoin(tpm, str);
	}
	free(str);
	free(tpm);
	return (1);
}

int parse_command(t_lists *lst)
{
    while (lst)
    {
        if (lst->token->type == literal)
        {
			check_variable(lst->token);
            if (check_builtins(lst->token))
                if (check_content(lst->token))
                    if (!check_cmd(lst->token))
                        return (0);
        }
        lst = lst->next;
    }
    return (1);
}