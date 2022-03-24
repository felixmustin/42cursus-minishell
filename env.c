#include "minishell.h"

int env_len(char **envv)
{
    int i;

    i = 0;
    while (envv[i])
        i++;
    return (i);
}

void free_env(char **envv)
{
    int i;
    int j;

    j = 0;
    i = env_len(envv);
    while(j < i)
    {
        free(envv[j]);
        envv[j] = NULL;
        j++;
    }
    free(envv);
    envv = NULL;
}

void init_env(char **envv)
{
    int i;

    env = malloc(sizeof(char *) * (env_len(envv) + 1));
    i = 0;
    while (envv[i])
    {
        env[i] = ft_strdup(envv[i]);
        i++;
    }
    env[i] = 0;
}