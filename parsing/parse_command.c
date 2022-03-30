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

int	set_path(char *cmd, char **str)
{
	int		i;
	char	**path;
	char	**tpm;
	char	*str;

	i = 0;
	while (env && !check_env(env[i]))
		i++;
	str = ft_substr(env[i], 5, ft_strlen);
	tpm = ft_split(str, ':');
	i = 0;
	while (tpm)
		i++;
	path = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (tpm)
	{
		path[i] = ft_strjoin(tpm[i], cmd);
		i++;
	}
	i = check_acces(path);
	if (i == -1)
		return (0);
	*str = ft_strdup(path[i]);
	return (1);
}

int	check_cmd(char **str)
{
	char	*tpm;
	char	*cmd;
	int		i;

	i = 0;
	while (*str[i] != '\0' && *str[i] != 32)
		i++;
	tpm = ft_substr(str, 0, i);
	cmd = ft_strjoin("/", tpm);
	free(tpm);
	if (!set_path(cmd, str))
		return (0);
	return (1);
}

int	parse_command(t_list *lst)
{
	while (lst)
	{
		if (lst->token->type == literal)
			if (!check_cmd(&lst->token->content))
				return (0);
	}
	return (1);
}