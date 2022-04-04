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
#include "get_next_line/get_next_line.h"

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

typedef struct s_lists
{
	t_token			*token;
	struct s_lists	*next;
    struct s_lists   *prev;
}	t_lists;

typedef struct s_cmd
{
    int     type; //0:exec  1-7:builtins
    char    **cmd;
	int     fd_i;
    int     fd_o;
    int     pipe_i; //0:no  1: | 2:&&  3:||
    int     pipe_o; //0:no  1: | 2:&&  3:||
} t_cmd;


typedef struct s_all_cmd
{
    struct s_cmd *cmds;
    int nbrcmd;
    int **pipefd;

} t_all_cmd;

char **env;

void ft_putstr(char *str);

//env
void	init_env(char **envv);
void	free_env(char **envv);
int     env_len(char **envv);

char	*new_prompt(void);

//parsing
int	check_quotes(t_lists *lst);
int	check_operator(t_lists *lst);
int	parse_command(t_lists *lst);
int set_cmd(t_all_cmd *all_cmd, t_lists *lst);
int	parsing(t_all_cmd *all_cmd, t_lists *lst);

//parsing_utils
void init_struct(t_cmd *cmd);
int count_cmd(t_lists *lst);
int get_type(char **str);

//token
t_token	*create_token(char *content, t_token_type type);
int	token(char *input, t_lists **lst);
t_lists	*newlst(t_token *token);
void	add_back(t_lists **lst, t_lists *new);
t_lists	*first_lst(t_lists *lst);

int	second_token(t_lists **lst);
int third_token(t_lists **lst);

//parse_redir
int get_redir_l(t_token *token);
int get_redir_dl(t_token *token);
int get_redir_r(t_token *token);
int get_redir_dr(t_token *token);

//pipe
void init_pipes(t_all_cmd *all_cmd);
void close_pipes(t_all_cmd *all_cmd);
void free_pipe(t_all_cmd *all_cmd);

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

char **dup_env(void);

#endif