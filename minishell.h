#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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
    char			*content;
    t_token_type	type;

} t_token;

typedef struct s_list
{
	t_token			*token;
	struct s_list	*next;
    struct s_list   *prev;
}	t_list;

typedef struct s_cmd
{
    int     type; //0:exec  1-7:builtins
    char    **cmd; //even with builtin (for args)
	int     fd_i;
    int     fd_o;
    int     pipe_i; //0:no  1:yes
    int     pipe_o;
    int     type_pipe; //0:no pipe  1:|  2:&&  3:||
} t_cmd;


typedef struct s_all_cmd
{
    struct s_cmd *cmds;
    int nbrcmd;
    int **pipefd;

} t_all_cmd;

char **env;

void	init_env(char **envv);
void	free_env(char **envv);

char	*new_prompt(void);
int		set_cmd(t_all_cmd *all_cmd, t_list *lst);
t_list	*newlst(t_token *token);
void	add_back(t_list **lst, t_list *new);
t_token	*create_token(char *content, t_token_type type);
void init_struct(t_cmd *cmd);
int	check_quotes(t_list *lst);
int	check_operator(t_list *lst);
t_list	*first_lst(t_list *lst);

//execution
void execute(t_all_cmd *all_cmd);
void handle_pipe(t_all_cmd *all_cmd, int i);
void handle_redir(t_cmd *cmd);

//builtins
void ex_echo(t_cmd *cmd);
void ex_cd(t_cmd *cmd);
void ex_pwd(void);
void ex_export(t_cmd *cmd);
void ex_unset(t_cmd *cmd);
void ex_env(void);

#endif