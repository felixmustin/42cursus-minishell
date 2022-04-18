#include "../../includes/minishell.h"

void close_fd(t_all_cmd *all_cmd)
{
    int i;

    i = -1;
    while (++i < all_cmd->nbrcmd)
    {
        if (all_cmd->cmds[i].fd_i != 0)
        {
            close(all_cmd->cmds[i].fd_i);
            if (all_cmd->cmds[i].type > 0 && all_cmd->cmds[i].pipe_i == 0 && all_cmd->cmds[i].pipe_o == 0)
            {
                dup2(all_cmd->cmds[i].saved_stdin, STDIN_FILENO);
                close(all_cmd->cmds[i].saved_stdin);
            }
        }
        if (all_cmd->cmds[i].fd_o != 1)
        {
            all_cmd->cmds[i].fd_o = 1;
            if (all_cmd->cmds[i].type > 0 && all_cmd->cmds[i].pipe_i == 0 && all_cmd->cmds[i].pipe_o == 0)
            {
                dup2(all_cmd->cmds[i].saved_stdout, STDOUT_FILENO);
                close(all_cmd->cmds[i].saved_stdout);
            }
        }
    }
}

void print_error_msg(t_all_cmd *all_cmd, int j)
{
    if (all_cmd->status == 127)
        printf("minishell: %s: command not found\n", all_cmd->cmds[j].cmd[0]);
    else if (all_cmd->status == 126)
        printf("minishell: %s: Permission denied\n", all_cmd->cmds[j].cmd[0]);
}

void status_child(t_all_cmd *all_cmd, int j, int status)
{
    int tmp;

    tmp = WEXITSTATUS(status);
    if (WIFEXITED(status))
        all_cmd->status = tmp;
    if(WIFSIGNALED(status))
    {
        all_cmd->status = WTERMSIG(status);
        if (all_cmd->status != 131)
            all_cmd->status += 128;
        return ;
    }
    if (all_cmd->cmds[j].type > 0)
        all_cmd->status = tmp;
    else
    {
        if (tmp == 1)
            all_cmd->status = 1;
        else if (tmp == 2)
            all_cmd->status = 127;
        else if (tmp == 13)
            all_cmd->status = 126;
        print_error_msg(all_cmd, j);
    }
}

void wait_pid(t_all_cmd *all_cmd, int i)
{
    int status;
    int j;

    j = 0;
    if (all_cmd->nbrcmd == 1 && all_cmd->cmds[0].type > 0)
        return ;
    else
    {
        while (i > j)
        {
            waitpid(all_cmd->pids[j], &status, 0);
            status_child(all_cmd, j, status);
            j++;
        }
        if (all_cmd->cmds[--j].type == 7)
            all_cmd->status = WEXITSTATUS(status);
	    free(all_cmd->pids);
    }
}

void exit_cmds(t_all_cmd *all_cmd, int i)
{
    close_fd(all_cmd);
    close_pipes(all_cmd);
    wait_pid(all_cmd, i);
    
    free_pipe(all_cmd);
}