#include "../minishell.h"

int get_redir_l(t_token *token)
{
    int fd;

    fd = open(token->content, O_RDONLY);
    if (!fd)
        return (0);
    return (fd);
}

int get_redir_dl(t_token *token)
{
    char *line;
    int size;
    int fd;

    fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666); //delete after
    if (!fd)
        return (0);
    size = ft_strlen(token->content);
    line = get_next_line(0);
    while(line)
    {
        if (strncmp(line, token->content, size));
            break ;
        ft_putstr_fd(line, fd);
        free(line);
        line = get_next_line(0);
    }
    free(line);
    return(fd);
}

int get_redir_r(t_token *token)
{
    int fd;
    
    fd = open(token->content, O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (!fd)
        return (0);
    return (fd);
}

int get_redir_dr(t_token *token)
{
    int fd;
    
    fd = open(token->content, O_CREAT | O_RDWR | O_APPEND, 0666);
    if (!fd)
        return (0);
    return (fd);
}

struct s_cmd get_pipe(t_cmd cmd, t_token *token)
{
    if (token->type == pipeline)
        cmd.pipe_o = 1; 
    if (token->type == and)
        cmd.pipe_o = 2;
    if (token->type == or)
        cmd.pipe_o = 3;
    return (cmd);
}

struct s_cmd parse_cmds(t_list *lst, int i)
{
    t_cmd full_cmd;

    init_struct(&full_cmd);
    while(lst)
    {
        if (lst->token->type == literal)
            full_cmd.cmd = create_cmd(lst->token);
        else if (lst->token->type == simple_redir_right)
            full_cmd.fd_o = get_redir_r(lst->token);
        else if (lst->token->type == simple_redir_left)
            full_cmd.fd_i = get_redir_l(lst->token);
        else if (lst->token->type == double_redir_right)
            full_cmd.fd_o = get_redir_dr(lst->token);
        else if (lst->token->type == double_redir_left)
            full_cmd.fd_i = get_redir_dl(lst->token);
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
        if (i > 0)
            all_cmd->cmds[i].pipe_i = all_cmd->cmds[i - 1].pipe_o;
        i++;
    }
}

int parsing (t_all_cmd *all_cmd, t_list *lst)
{
    all_cmd->nbrcmd = count_cmd(lst);
    //check_cmd(lst);
    //expand_var(lst);
    interpreter(lst, all_cmd);
}