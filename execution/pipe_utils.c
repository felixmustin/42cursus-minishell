#include "minishell.h"

int	*init_pipes(int nb_pipes)
{
	int		i;
	int		*pipes;

	i = -1;
	pipes = malloc(sizeof(int) * 2 * nb_pipes);
	while (++i < nb_pipes)
	{
		pipe(pipes + i * 2);
	}
	return (pipes);
}

void	close_pipes(int *pipes, int nb)
{
	int		i;

	i = -1;
	while (++i < nb * 2)
	{
		close(pipes[i]);
	}
}