#include "../../includes/minishell.h"

void ex_pwd(t_all_cmd *all_cmd, int i)
{
    char *str;
    char *str2;
    char *cwd;

    if (all_cmd->cmds[i].cmd[1])
    {
        if (all_cmd->cmds[i].cmd[1][0] == '-')
        {
            all_cmd->status = 1;
            str = ft_strjoin("minishell: pwd: ", all_cmd->cmds[i].cmd[1]);
            str2 = ft_strjoin(str, " invalid option\n");
            ft_putstr_fd(str2, STDERR_FILENO);
            free(str);
            free(str2);
            return ;
        }
    }
    cwd = getcwd(NULL, 0);
    ft_putstr(cwd);
    ft_putstr("\n");
    free(cwd);
    return ;
}