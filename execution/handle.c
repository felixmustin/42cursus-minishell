#include "minishell.h"

void handle_pipe_1(t_cmd *cmd, int pipefd[2])
{
    if (cmd->pipe_i == 1)
    {
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
            return (perror("dup"));
    }
    if (cmd->pipe_o == 1)
    {
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
            return (perror("dup"));
    }
}

void handle_pipe_2(t_cmd *cmd, int pipefd[2]) // &&
{

}

void handle_pipe_3(t_cmd *cmd, int pipefd[2]) // ||
{

}

void handle_pipe(t_cmd *cmd, int pipefd[2])
{
    if (cmd->type_pipe == 1)
        handle_pipe_1(cmd, pipefd)
    if (cmd->type_pipe == 2)
        handle_pipe_2()
    if (cmd->type_pipe == 3)
        handle_pipe_3()
}
