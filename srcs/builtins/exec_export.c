#include "../../includes/minishell.h"

int	check_if_exist(char *str, int j)
{
	char	*cut_str;
	int		i;
	int		k;

	i = 0;
	while (str[i] != '=')
		i++;
	cut_str = ft_substr(str, 0, i + 1);
	k = 0;
	while (k < j)
	{
		if (!ft_strncmp(env[k], cut_str, i + 1))
		{
			free(env[k]);
			env[k] = ft_strdup(str);
			return (0);
		}
		k++;
	}
	return (1);
}

int	check_if_val(t_all_cmd *all_cmd, int k, int j, int ind)
{
	int	i;

	i = 0;
	if (all_cmd->cmds[k].cmd[j][i] < 65 || all_cmd->cmds[k].cmd[j][i] > 122)
	{
		if (ind)
			print_error(all_cmd, k, j);
		return (0);
	}
	i++;
	while (all_cmd->cmds[k].cmd[j][i] >= 65
			&& all_cmd->cmds[k].cmd[j][i] <= 122)
		i++;
	if (all_cmd->cmds[k].cmd[j][i] != '=')
		return (0);
	return (1);
}

char	**dup_env(void)
{
	char		**tmp_env;
	int			len;
	int			i;

	len = env_len(env);
	tmp_env = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		tmp_env[i] = ft_strdup(env[i]);
		i++;
	}
	tmp_env[i] = 0;
	return (tmp_env);
}

void	init_env_add(t_all_cmd *all_cmd, int k, char **tmp_env)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = 1;
	while (all_cmd->cmds[k].cmd[++i])
	{
		if (check_if_val(all_cmd, k, i, 1))
			len++;
	}
	env = malloc(sizeof(char *) * (env_len(tmp_env) + len));
	i = -1;
	while (tmp_env[++i])
		env[i] = ft_strdup(tmp_env[i]);
	j = 0;
	while (all_cmd->cmds[k].cmd[++j])
	{
		if (check_if_val(all_cmd, k, j, 0))
		{
			if (check_if_exist(all_cmd->cmds[k].cmd[j], i))
				env[i++] = ft_strdup(all_cmd->cmds[k].cmd[j]);
		}
	}
	env[i] = 0;
}

void	ex_export(t_all_cmd *all_cmd, int j)
{
	int		i;
	char	**tmp_env;

	if (check_valid_exp(all_cmd, j))
		return ;
	if (!all_cmd->cmds[j].cmd[1])
	{
		i = 0;
		while (env[++i])
			printf("declare -x %s\n", env[i]);
	}
	else
	{
		tmp_env = dup_env();
		free_env(env);
		init_env_add(all_cmd, j, tmp_env);
		free_env(tmp_env);
	}
	return ;
}
