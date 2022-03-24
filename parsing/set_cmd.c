#include "../minishell.h"

t_cmd get_pipe(t_cmd full_cmd, t_token *token)
{
    if (token->type == pipeline)
        full_cmd.type_pipe = 0; 
    if (token->type == and)
        full_cmd.type_pipe = 1;
    if (token->type == or)
        full_cmd.type_pipe = 2;
    full_cmd.pipe_o = 1;
}

struct s_cmd parse_cmds(t_list *lst, int i)
{

    t_cmd full_cmd;

    init_struct(&full_cmd);
    if (i > 0)
        full_cmd.pipe_i = 1;
    while(lst)
    {
        if (lst->token->type == literal)
            full_cmd.cmd = create_cmd(lst->token);
        else if (lst->token->type == simple_redir_right)
            full_cmd.fd_o = get_redir(lst->token);
        else if (lst->token->type == simple_redir_left)
            full_cmd.fd_i = get_redir(lst->token);
        else if (lst->token->type == double_redir_right)
            full_cmd.fd_o = get_redir(lst->token);
        else if (lst->token->type == double_redir_left)
            full_cmd.fd_i = get_redir(lst->token);
        else if (lst->token->type == (pipeline || and || or))
            return(get_pipe(full_cmd, lst->token));
        lst = lst->next;
    }
    return (full_cmd);
}

int interpreter(t_list *lst, t_all_cmd *all_cmd)
{
    int i;

    all_cmd->cmds = malloc(sizeof(t_cmd) * all_cmd->nbrcmd);
    if (!all_cmd->cmds)
        return (0);
    i = 0;
    while (i < all_cmd->nbrcmd)
    {
        all_cmd->cmds[i] = parse_cmds(lst, i);
        i++;
    }
}

int parsing (t_all_cmd *all_cmd, t_list *lst)
{
    all_cmd->nbrcmd = count_cmd(lst);
    //check_cmd(lst); //peut etre autre part (plusieurs check?)
    //expand_var(lst);
    //...
    interpreter(lst, all_cmd);
}