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

int main(int argc, char **argv, char **envv)
{
    t_all_cmd all_cmd;
    t_list *lst;
    char *input;
    char *cwd;

    init_env(envv);
    signal(SIGINT, signal_handler);
    cwd = new_prompt();
    while ((input = readline(cwd)) != NULL)
    {
        if (ft_strlen(input) > 0)
            add_history(input);
        token(input, &lst);
        parsing(&all_cmd, lst);
        execute(&all_cmd);
        free(input);
    }
    free(cwd);
    free_env();
}