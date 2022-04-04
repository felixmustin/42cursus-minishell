#include "minishell.h"

/*void init_term(void)
{
    struct termios termios;

    //tcgetattr(0, &termios);
    //termios.c_cc[VEOF]  = 3; // ^C
    //termios.c_cc[VINTR] = 4; // ^D
    //tcsetattr(0,TCSANOW,&termios);
}*/

void signal_handler(int sign)
{
    if (sign == SIGINT)
	{
        ft_putstr_fd("\n", 0);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
	}
}

void close_fd(t_all_cmd *all_cmd)
{
    int i;

    i = 0;
    while (i < all_cmd->nbrcmd)
    {
        if (all_cmd->cmds[i].fd_i != 0)
            close(all_cmd->cmds[i].fd_i);
        if (all_cmd->cmds[i].fd_o != 1)
            close(all_cmd->cmds[i].fd_o);
        i++;
    }
}

void free_cmds(t_all_cmd *all_cmd)
{
    int i;
    int j;

    i = 0;
    while (i < all_cmd->nbrcmd)
    {
        j = 0;
        while (all_cmd->cmds[i].cmd[j])
        {
            free(all_cmd->cmds[i].cmd[j]);
            j++;
        }
        free(all_cmd->cmds[i].cmd);
        i++;
    }
    close_fd(all_cmd);
    free(all_cmd->cmds);
}

int main(int argc, char **argv, char **envv)
{
    t_all_cmd all_cmd;
    t_lists *lst;
    char *input;
    char *cwd;

    init_env(envv);
    signal(SIGINT, signal_handler);
    cwd = new_prompt();
    lst = NULL;
    while ((input = readline(cwd)) != NULL)
    {
        if (ft_strlen(input) > 0)
            add_history(input);
        if (ft_strlen(input))
        {
            token(input, &lst);
            second_token(&lst);
            third_token(&lst);
            ft_putstr(lst->token->content);
            if (parsing(&all_cmd, lst))
            {
                execute(&all_cmd);
                free_cmds(&all_cmd);
            }
        }
        free(input);
    }
    free(cwd);
    free_env(env);
}