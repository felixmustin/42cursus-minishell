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
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"
# define DEFAULT "\001\033[0;39m\002"

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
	undesirable,
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
    struct s_lists	*prev;
}	t_lists;

typedef struct s_cmd
{
    int		type; //-1: no cmd 0:exec  1-7:builtins
    char	**cmd;
	int		fd_i;
    int		fd_o;
    int		pipe_i; //0:no  1: | 2:&&  3:||
    int		pipe_o; //0:no  1: | 2:&&  3:||
    int		saved_stdin;
    int		saved_stdout;
} t_cmd;

typedef struct s_all_cmd
{
    struct s_cmd	*cmds;
    int 			nbrcmd;
    int 			**pipefd;
    int             status;
    pid_t           *pids;
} t_all_cmd;

char	**env;
void	ft_putstr(char *str);
//env
void	init_env(char **envv);
void	free_env(char **envv);
int		env_len(char **envv);
char	*new_prompt(void);
//parsing
int		check_quotes_op(char **input);
int		unclosed_quotes(char **input);
int		check_operator(char **input, int i);
int		unclosed_operator(char **input);
int		parse_command(t_lists *lst);
int		set_cmd(t_all_cmd *all_cmd, t_lists *lst);
int		parsing(t_all_cmd *all_cmd, char **input, t_lists **lst, int status);
void	free_cmds(t_all_cmd *all_cmd);
//parsing_utils
void	init_struct(t_cmd *cmd);
int		count_cmd(t_lists *lst);
int		get_type(char **str);
int     print_syntax_error(char *str, int i);
//token
int		main_token(char *input, t_lists **lst, int status);
t_token	*create_token(char *content, t_token_type type);
int		token(char *input, t_lists **lst);
t_lists	*newlst(t_token *token);
void	add_back(t_lists **lst, t_lists *new);
t_lists	*first_lst(t_lists *lst);
int		second_token(t_lists **lst, int status);
int		third_token(t_lists **lst);
void	free_lst(t_lists **lst);
int		delete_quotes(t_lists **lst);
int		check_variable(t_lists **lst);
int		search_variable(char **str);
int		set_variable(t_lists **lst);
int		check_status(char **str, int status);
//parse_redir
int		get_redir_l(t_token *token);
int		get_redir_dl(t_token *token);
int		get_redir_r(t_token *token);
int		get_redir_dr(t_token *token);
//pipe
void	init_pipes(t_all_cmd *all_cmd);
void	close_pipes(t_all_cmd *all_cmd);
void	free_pipe(t_all_cmd *all_cmd);
//execution
void	execute(t_all_cmd *all_cmd);
void	handle_pipe(t_all_cmd *all_cmd, int i);
void	handle_redir(t_cmd *cmd);
void    handle_redir_fork(t_cmd *cmd);
void    exit_cmds(t_all_cmd *all_cmd, int i);
//builtins
void    ex_exit(t_all_cmd *all_cmd, int i);
void    ex_echo(t_all_cmd *all_cmd, int i);
void    ex_cd(t_all_cmd *all_cmd, int i);
void    ex_pwd(t_all_cmd *all_cmd, int i);
void    ex_export(t_all_cmd *all_cmd, int i);
int     check_valid_exp(t_all_cmd *all_cmd, int j);
void    print_error(t_all_cmd *all_cmd, int j, int i);
void    ex_unset(t_all_cmd *all_cmd, int i);
void    ex_env(t_all_cmd *all_cmd, int i);
char	**dup_env(void);
//signal
void	signal_handler(int sign);

#endif