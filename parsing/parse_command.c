#include "../minishell.h"

int	check_env(char *str)
{
	if (str[0] == 'P')
		if (str[1] == 'A')
			if (str[2] == 'T')
				if (str[3] == 'H')
					return (1);
	return (0);	
}

int	check_acces(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (access(str[i], F_OK) != -1 && access(str[i], X_OK) != -1)
			return (i);
		i++;
	}
	return (-1);
}

int set_path(char *cmd, t_token *token)
{
	int		j;
	int		i;
	char	**path;
	char	**tpm;
	char	*sstr;
	char	*tok_tmp;

	i = 0;
	while (env && !check_env(env[i]))
		i++;
	sstr = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	tpm = ft_split(sstr, ':');
	i = 0;
	while (tpm[i])
		i++;
	path = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (tpm[i])
	{
		path[i] = ft_strjoin(tpm[i], cmd);
		i++;
	}
	i = check_acces(path);
	if (i == -1)
		return (0);
	j = 0;
	while(token->content[j] != ' ')
		j++;
	tok_tmp = ft_substr(token->content, j, ft_strlen(token->content) - j);
	free(token->content);
	token->content = NULL;
	token->content = ft_strjoin(path[i], tok_tmp);
	ft_putstr(token->content);
	return (1);
}

int check_cmd(t_token *token)
{
	char 	*ret;
	char	*tpm;
	char	*cmd;
	int		i;

	i = 0;
	while (token->content[i] != '\0' && token->content[i] != 32)
		i++;
	tpm = ft_substr(token->content, 0, i);
	cmd = ft_strjoin("/", tpm);
	free(tpm);
	if (!set_path(cmd, token))
		return (0);
	return (1);
}

int	parse_command(t_lists *lst)
{
	while (lst)
	{
		if (lst->token->type == literal)
			if (!check_cmd(lst->token))
				return (0);
		lst = lst->next;
	}
	return (1);
}