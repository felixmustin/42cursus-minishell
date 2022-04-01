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
        if (strncmp(line, token->content, size))
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