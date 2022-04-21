#include "../includes/minishell.h"

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

void main_exec(char **input, t_lists **lst)
{
    t_all_cmd all_cmd;

    if (ft_strlen(*input) > 0)
    	add_history(*input);
    if (ft_strlen(*input))
    {
    	if (parsing(&all_cmd, input, lst))
		{
   	 	    execute(&all_cmd);
			set_sig_code(all_cmd.status);
     		free_cmds(&all_cmd);
		}
		free_lst(lst);
   	}
}


int main(int argc, char **argv, char **envv)
{
    char *input;
    t_lists *lst;
    char *cwd;

	if (argc > 0 && argv)
	{
        cmd_signals(0);
    	init_env(envv);
    	lst = NULL;
    	cwd = new_prompt();
    	while ((input = readline(cwd)) != NULL)
        {
            main_exec(&input, &lst);
            ft_free(input);
            ft_free(cwd);
            cwd = new_prompt();
            cmd_signals(0);
        }
    	free_env(env);
	}
}