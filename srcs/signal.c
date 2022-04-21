#include "../includes/minishell.h"

static void	cmd_signal_handler(int sign)
{
	if (sign == SIGINT)
	{
		set_sig_code(130);
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

static void	input_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		set_sig_code(1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

static void	global_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		set_sig_code(1);
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	cmd_signals(int i)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (i == 1)
		signal(SIGINT, cmd_signal_handler);
	if (i == 0)
		signal(SIGINT, global_signal_handler);
}

void	input_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, input_signal_handler);
}