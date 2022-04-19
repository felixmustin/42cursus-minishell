#include "../includes/minishell.h"

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

void free_cmds(t_all_cmd *all_cmd)
{
    int i;
    int j;

    i = 0;
    while (i < all_cmd->nbrcmd)
    {
        if (all_cmd->cmds[i].type >= 0)
        {
            j = 0;
            while (all_cmd->cmds[i].cmd[j])
            {
                free(all_cmd->cmds[i].cmd[j]);
                all_cmd->cmds[i].cmd[j] = NULL;
                j++;
            }
            free(all_cmd->cmds[i].cmd);
        }
        i++;
    }
    free(all_cmd->cmds);
}

int main(int argc, char **argv, char **envv)
{
    t_all_cmd all_cmd;
    t_lists *lst;
    char *input;
    char *cwd;
	int	status;

	status = 0;
	if (argc > 0 && argv)
	{
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
    	        if (parsing(&all_cmd, &input, &lst, status))
				{
   	 	        	execute(&all_cmd);
					status = all_cmd.status;
     		       	free_cmds(&all_cmd);
				}
				free_lst(&lst);
   	     	}
        	free(input);
            free(cwd);
            cwd = new_prompt();
    	}
    	free_env(env);
	}
}