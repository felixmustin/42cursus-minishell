#include "main.h"

void env_builtin(void)
{
    int i;

    i = 0;
    while(env[++i])
    {
        ft_putstr_fd(env[i], 0);
        ft_putstr_fd("\n", 0);
    }
}

void pwd_builtin(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    ft_putstr_fd(cwd, 0);
    ft_putstr_fd("\n", 0);
    free(cwd);
}

void echo_builtin(char *str, int option)
{
    if (option == 0)
        ft_putstr_fd(str, 0);
}