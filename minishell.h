#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line_bonus.h"

typedef enum s_token_type
{
    literal,
    space,
    and,
	or,
	simple_redir_left,
	simple_redir_right,
	double_redir_left,
	double_redir_right,
	pipeline,
	single_quote,
	double_quote,
	variable,
	backslash,
}   t_token_type;

typedef struct s_token
{
    char			content;
    t_token_type	type;

} t_token;

typedef struct s_list
{
	t_token			*token;
	struct s_list	*next;
}	t_list;

char **env;

void	init_env(char **envv);
void	free_env(void);
void	env_builtin(void);
void	pwd_builtin(void);
void	echo_builtin(char *str, int option);
char	*new_prompt(void);
int		parsing(t_list *lst);
t_list	*newlst(t_token *token);
void	add_back(t_list **lst, t_list *new);
t_token	*create_token(void *content, t_token_type type);


#endif