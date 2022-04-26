/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:45:02 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 14:50:13 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_path_2(char **path, char **cmd)
{
	int	i;

	i = check_acces(path);
	if (i == -1)
	{
		free_env(path);
		return (0);
	}
	ft_free(*cmd);
	*cmd = ft_strdup(path[i]);
	free_env(path);
	return (1);
}

int	set_path(char **cmd)
{
	int		i;
	char	**path;
	char	**tpm;
	char	*str;

	i = 0;
	while (g_env[i] && !check_env(g_env[i]))
		i++;
	str = ft_substr(g_env[i], 5, ft_strlen(g_env[i]));
	tpm = ft_split(str, ':');
	i = 0;
	if (!tpm)
		return (0);
	while (tpm[i])
		i++;
	path = malloc(sizeof(char *) * (i + 1));
	if (!path)
		return (0);
	i = -1;
	while (tpm[++i])
		path[i] = ft_strjoin(tpm[i], *cmd);
	path[i] = NULL;
	return (set_path_2(path, cmd));
}

int	check_cmd(t_token *token)
{
	char	*tpm;
	char	*cmd;
	char	*str;
	int		i;

	i = 0;
	if (!ft_strncmp(token->content, ".", ft_strlen(token->content) - 1)
		|| !ft_strncmp(token->content, "/", ft_strlen(token->content) - 1))
		return (0);
	while (token->content[i] != '\0' && token->content[i] != 32
		&& token->content[i] != -1)
		i++;
	if (i == 0)
		return (0);
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

int	check_builtins(t_token *token)
{
	char	*str;
	int		i;

	i = 0;
	while (token->content[i] != '\0' && token->content[i] != 32)
		i++;
	str = ft_substr(token->content, 0, i);
	i = 1;
	if (ft_strncmp(str, "pwd", 3) == 0)
		i = 0;
	if (ft_strncmp(str, "echo", 4) == 0)
		i = 0;
	if (ft_strncmp(str, "cd", 2) == 0)
		i = 0;
	if (ft_strncmp(str, "export", 6) == 0)
		i = 0;
	if (ft_strncmp(str, "unset", 5) == 0)
		i = 0;
	if (ft_strncmp(str, "env", 3) == 0)
		i = 0;
	if (ft_strncmp(str, "exit", 4) == 0)
		i = 0;
	free(str);
	return (i);
}

int	parse_command(t_lists *lst)
{
	while (lst)
	{
		if (lst->token->type == literal)
		{
			if (check_builtins(lst->token))
				check_cmd(lst->token);
		}
		lst = lst->next;
	}
	return (1);
}
