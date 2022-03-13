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

char **env;

void init_env(char **envv);
void free_env(void);

void env_builtin(void);
void pwd_builtin(void);
void echo_builtin(char *str, int option);

char *new_prompt(void);


char *parsing(char *input);


#endif