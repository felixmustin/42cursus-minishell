#include "../../includes/minishell.h"

void ex_pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    ft_putstr(cwd);
    ft_putstr("\n");
    free(cwd);
}