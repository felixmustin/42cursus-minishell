#include "minishell.h"

void init_env_suppr(char *str, char **tmp_env)
{
    int len;
    int i;
    int j;

    env = malloc(sizeof(char *) * (env_len(tmp_env)));
    len = ft_strlen(str);
    i = -1;
    while (tmp_env[++i])
    {
        if (ft_strncmp(tmp_env[i], str, len) != 0)
            env[i] = ft_strdup(tmp_env[i]);
    }
    env[i] = 0;
}

void ex_unset(t_cmd *cmd)
{
    char **tmp_env;
    int i;

    i = 1;
    while(cmd->cmd[i])
    {
        tmp_env = dup_env();
        free_env(env);
        init_env_suppr(cmd->cmd[i], tmp_env);
        free_env(tmp_env);
        i++;
    }
}