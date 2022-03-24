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

void free_pipe(t_all_cmd *all_cmd)
{
    int i;

    i = 0;
    while (i < all_cmd->nbrcmd - 1)
        free(all_cmd->pipefd[i]);
    free(all_cmd->pipefd);
}