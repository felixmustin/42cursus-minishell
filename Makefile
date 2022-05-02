SRCS	=	srcs/main.c \
			srcs/utils.c \
			srcs/prompt.c \
			srcs/env.c \
			srcs/signal.c \
			srcs/builtins/exec_cd.c \
			srcs/builtins/exec_echo.c \
			srcs/builtins/exec_env.c \
			srcs/builtins/exec_export.c \
			srcs/builtins/exec_export_2.c \
			srcs/builtins/exec_pwd.c \
			srcs/builtins/exec_unset.c \
			srcs/builtins/exec_exit.c \
			srcs/execution/execute.c \
			srcs/execution/handle_pipe.c \
			srcs/execution/handle_redir.c \
			srcs/execution/pipe_utils.c \
			srcs/execution/exit.c \
			srcs/parsing/check_quotes.c \
			srcs/parsing/check_quotes_op.c \
			srcs/parsing/parse_command.c \
			srcs/parsing/parse_command_2.c \
			srcs/parsing/parse_redir.c \
			srcs/parsing/parsing_utils.c \
			srcs/parsing/parsing.c \
			srcs/parsing/set_cmd.c \
			srcs/parsing/check_operator.c \
			srcs/token/free_token.c \
			srcs/token/lst_move.c \
			srcs/token/main_token.c \
			srcs/token/second_token.c \
			srcs/token/third_token.c \
			srcs/token/token.c \
			srcs/token/check_variable.c \
			srcs/token/delete_quotes.c \
			srcs/token/set_variable.c \
			srcs/token/token_utils.c \
			get_next_line/get_next_line.c \

INCL		= includes/minishell.h
OBJS		= ${SRCS:.c=.o}
NAME		= minishell
LIBFT_DIR	= libft/
LIBFT		= ${LIBFT_DIR}libft.a
CC			= gcc
CCFLAGS		= -Wall -Wextra -Werror -I ${INCL} -I ${LIBFT_DIR} -fsanitize=address

%.o: %.c
	$(CC) $(CCFLAGS) -I/Users/$(USER)/.brew/opt/readline/include -c $< -o $@

all:	${LIBFT} ${INCL} ${NAME}

${NAME}:	${OBJS} ${INCL}
					$(CC) $(CCFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

${LIBFT}:
			@make -C./libft

clean:
			rm -f ${OBJS}
			@make clean -C ./libft

fclean:	clean
			rm -f ${NAME}
			rm -f ${LIBFT}

re:		fclean all

.PHONY:	all clean fclean re
