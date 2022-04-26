/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:06:49 by fmustin           #+#    #+#             */
/*   Updated: 2022/04/26 12:06:51 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_pipe_1(t_cmd *cmd, int **pipefd, int i)
{
	if (cmd->pipe_i == 1)
	{
		close(pipefd[i - 1][1]);
		if (dup2(pipefd[i - 1][0], STDIN_FILENO) == -1)
			return (perror("dup"));
		close(pipefd[i - 1][0]);
	}
	if (cmd->pipe_o == 1)
	{
		close(pipefd[i][0]);
		if (dup2(pipefd[i][1], STDOUT_FILENO) == -1)
			return (perror("dup"));
		close(pipefd[i][1]);
	}
}

void	handle_pipe(t_all_cmd *all_cmd, int i)
{
	if (all_cmd->cmds[i].pipe_i == 1 || all_cmd->cmds[i].pipe_o == 1)
		handle_pipe_1(&all_cmd->cmds[i], all_cmd->pipefd, i);
}
