/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:06:59 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 12:07:00 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipes(t_all_cmd *all_cmd)
{
	int	i;

	i = -1;
	all_cmd->pipefd = malloc(sizeof(int *) * (all_cmd->nbrcmd - 1));
	while (++i < (all_cmd->nbrcmd - 1))
		all_cmd->pipefd[i] = malloc(sizeof(int) * 2);
	i = -1;
	while (++i < (all_cmd->nbrcmd - 1))
		pipe(all_cmd->pipefd[i]);
}

void	close_pipes(t_all_cmd *all_cmd)
{
	int	i;

	i = -1;
	while (++i < (all_cmd->nbrcmd - 1))
	{
		close(all_cmd->pipefd[i][0]);
		close(all_cmd->pipefd[i][1]);
	}
}

void	free_pipe(t_all_cmd *all_cmd)
{
	int	i;

	i = -1;
	if (all_cmd->nbrcmd > 1)
	{
		while (++i < (all_cmd->nbrcmd - 1))
			free(all_cmd->pipefd[i]);
		free(all_cmd->pipefd);
	}
}
