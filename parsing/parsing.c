#include "../minishell.h"

void	check_builtins(t_list *lst)
{}

struct s_cmd parse_cmds(t_list *lst)
{
    t_cmd full_cmd;

    while(lst)
    {
        if (lst->token->type == literal) // /bin/echo
            full_cmd->cmd = create_cmd(lst->token);
        else if (lst->token->type = simple_redir_right)
            full_cmd->fd_out = get_redir(lst->token)
        else if (lst->token->type = simple_redir_left)
            full_cmd->fd_in = get_redir(lst->token)
         else if (lst->token->type = double_redir_right)
            full_cmd->fd_out = get_redir(lst->token)
        else if (lst->token->type = double_redir_left)
            full_cmd->fd_in = get_redir(lst->token)
        else if (lst->token->type == (pipeline || and || or))
            return(get_pipe_or_op(lst->token));
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
        all_cmds->cmds[i] = parse_cmds(lst);
        i++;
    }
}

int parsing (t_all_cmd *all_cmd, t_list *lst)
{
    all_cmd->nbrcmd = count_cmd(lst);
    //check_cmd(lst);
    //expand_var(lst);
    //..
    interpreter(lst, all_cmd);
}