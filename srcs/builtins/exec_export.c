#include "../../includes/minishell.h"

char **dup_env(void)
{
    char **tmp_env;
    int i;

    tmp_env = malloc(sizeof(char *) * (env_len(env)));
    i = 0;
    while (env[i])
    {
        tmp_env[i] = ft_strdup(env[i]);
        i++;
    }
    tmp_env[i] = 0;
    return (tmp_env);
}

void init_env_add(t_cmd *cmd, char **tmp_env)
{
    int len;
    int i;
    int j;

    len = 1;
    while (cmd->cmd[len])
        len++;
    env = malloc(sizeof(char *) * (env_len(tmp_env) + len));
    i = -1;
    while (tmp_env[++i])
        env[i] = ft_strdup(tmp_env[i]);
    j = 0;
    while (++j < len)
    {
        env[i] = ft_strdup(cmd->cmd[j]);
        i++;
    }
    env[i] = 0;
}

void display_exp_env(void)
{
    int i;

    i = 0;
    while(env[++i])
    {
        ft_putstr("declare -x ");
        ft_putstr(env[i]);
        ft_putstr("\n");
    }
}

void ex_export(t_cmd *cmd)
{
    char **tmp_env;

    if (!cmd->cmd[1])
        display_exp_env();
    else
    {
        tmp_env = dup_env();
        free_env(env);
        init_env_add(cmd, tmp_env);
        free_env(tmp_env);
    }
}