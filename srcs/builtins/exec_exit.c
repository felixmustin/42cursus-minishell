#include "../../includes/minishell.h"

int check_atoi(int nb, int signe)
{
    if (signe == 1)
    {
        while (nb > 255)
            nb -= 256;
    }
    else
    {
        nb *= signe;
        while (nb < 0)
            nb += 256;
    }
    return(nb);
}

int	ft_atoi_dif(const char *str)
{
	int					signe;
	unsigned long int	nb;
    unsigned long int   new;

	signe = 1;
	nb = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 43 || *str == 45 || (*str >= 48 && *str <= 57))
	{
		if (*str == 45)
			signe = -1;
	}
	else
		return (0);
	if (!(*str >= 48 && *str <= 57))
		str++;
	while (*str >= 48 && *str <= 57 && *str != '\0')
		nb = nb * 10 + (*str++ - '0');
    new = check_atoi(nb, signe);
	return (new);
}

void ex_exit(t_all_cmd *all_cmd, int i)
{
    int j;

    printf("exit\n");
    if (all_cmd->cmds[i].cmd[1])
    {
        j = 0;
        while (all_cmd->cmds[i].cmd[1][++j])
        {
            if (!ft_isdigit(all_cmd->cmds[i].cmd[1][j]))
            {
                all_cmd->status = 255;
                printf("minishell: exit: %s: numeric argument required\n",all_cmd->cmds[i].cmd[1]);
                exit(255);
            }
        }
        if (all_cmd->cmds[i].cmd[2])
        {
            all_cmd->status = 1;
            printf("minishell: exit: too many arguments\n");
        }
        else
            exit(ft_atoi_dif(all_cmd->cmds[i].cmd[1]));
    }
    else
        exit(0);
}