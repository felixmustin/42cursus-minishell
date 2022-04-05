#include "../../includes/minishell.h"

void ex_env(void)
{
    int i;

    i = 0;
    while(env[++i])
    {
        ft_putstr(env[i]);
        ft_putstr("\n");
    }
}