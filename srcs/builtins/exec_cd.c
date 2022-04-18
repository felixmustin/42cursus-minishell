#include "../../includes/minishell.h"

char *get_home(void)
{
    char *home;
    int len;
    int i;

    i = -1;
    while(env[++i])
    {
        if(ft_strnstr(env[i], "HOME=", 5))
        {
            len = ft_strlen(env[i]);
            home = ft_substr(env[i], 5, len - 5);
        }
    }
    return (home);
}

void set_env(char *type, char *pwd)
{
    int i;

    i = -1;
    while(env[++i])
    {
        if(ft_strnstr(env[i], "PWD=", 4) && !ft_strncmp("PWD", type, 3))
        {
            free(env[i]);
            env[i] = NULL;
            ft_strjoin("PWD=", pwd);
        }
        else if (ft_strnstr(env[i], "OLDPWD=", 7 && !ft_strncmp("OLDPWD", type, 6)))
        {
            free(env[i]);
            env[i] = NULL;
            ft_strjoin("OLDPWD=", pwd);
        }
    }
}

void exit_cd(t_all_cmd *all_cmd, int i)
{
    char *str;

    str = ft_strjoin("minishell: cd: ", all_cmd->cmds[i].cmd[1]);
    all_cmd->status = 1;
    perror(str);
    free(str);
}

void ex_cd(t_all_cmd *all_cmd, int i)
{
	int		ret;
	char	*old_pwd;
	char	*new_pwd;

    old_pwd = getcwd(NULL, 0);
	if (!all_cmd->cmds[i].cmd[1])
    {
        new_pwd = get_home();
		ret = chdir(new_pwd);
    }
    else
    {
        ret = chdir(all_cmd->cmds[i].cmd[1]);
        new_pwd = getcwd(NULL, 0);
    }
	if (ret == -1)
        return (exit_cd(all_cmd, i));
    set_env("PWD", new_pwd);
	set_env("OLDPWD", old_pwd);
	free(old_pwd);
	free(new_pwd);
    return ;
}