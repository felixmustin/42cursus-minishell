#include "minishell.h"

int	**init_pipes(int nb_pipes)
{
	int		i;
	int		**pipes;

	i = -1;
	pipes = malloc(sizeof(int *) * nb_pipes);
    while (++i < nb_pipes)
        pipes[i] = malloc(sizeof(int) * 2);
    i = -1;
	while (++i < nb_pipes)
		pipe(pipes[i]);
	return (pipes);
}

void	close_pipes(t_all_cmd *all_cmd)
{
	int		i;

	i = -1;
	while (++i < (all_cmd->nbrcmd - 1))
	{
		close(all_cmd->pipefd[i][0]);
        close(all_cmd->pipefd[i][1]);
	}
}

void handle_pipe_1(t_cmd *cmd, int **pipefd, int i)
{
    if (cmd->pipe_i == 1)
    {
        close(pipefd[i-1][1]);
        if (dup2(pipefd[i-1][0], STDIN_FILENO) == -1)
            return (perror("dup"));
        close(pipefd[i-1][0]);
    }
    if (cmd->pipe_o == 1)
    {
        close(pipefd[i][0]);
        if (dup2(pipefd[i][1], STDOUT_FILENO) == -1)
            return (perror("dup"));
        close(pipefd[i][1]);
    }
}

void handle_pipe(t_all_cmd *all_cmd, int i)
{
    if (all_cmd->cmds[i].type_pipe == 1)
        handle_pipe_1(&all_cmd->cmds[i], all_cmd->pipefd, i);
    /*if (all_cmd[i].cmds->type_pipe == 2)
        handle_pipe_2();
    if (all_cmd[i].cmds->type_pipe == 3)
        handle_pipe_3();*/
}
