#include "../../include/minishell.h"
#include "../../include/libft.h"

void    input_redir(t_data *data, t_ASTNode *node)
{
    ft_close(data->fd_in);
    data->fd_in = open(node->content, O_RDONLY, S_IRWXU);
    if (data->fd_in == -1)
    {
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(node->content, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
        data->ret = 1;
        data->no_exec = true;
        return ;
    }
    dup2(data->fd_in, STDIN);
}

int piping(t_data *data)
{
    pid_t   pid;
    int pipe_fd[2];

    pipe(pipe_fd);
    pid = fork();
    if (pid == 0)
    {
        ft_close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN);
        data->pipe_in = pipe_fd[0];
        data->pid = -1;
        data->parent = false;
        data->no_exec = false;
        return (2);
    }
    else
    {
        ft_close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT);
        data->pipe_out = pipe_fd[1];
        data->pid = pid;
        data->last = false;
        return (1);
    }
}
