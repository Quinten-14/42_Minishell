#include "../../include/minishell.h"
#include "../../include/libft.h"
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>

/* Helper function to throw the redirection error */

void    redir_error(char *file, t_data *data)
{
    ft_putstr_fd("minishell: ", STDERR);
    ft_putstr_fd(file, STDERR);
    ft_putendl_fd(": No such file or directory", STDERR);
    data->ret = 1;
    data->abort_exec = true;
}

/* Redir will be called if > or >> are the redirection needed */

void    redir(t_data *data, t_ASTNode *node)
{
    char    *file;

    file = ft_strdup(node->left->content);
    if (!file)
        return ((void)printf("Redirection Failed\n"));
    ft_close(data->fd_output);
    if (ft_strcmp(node->type, "great") == 0)
        data->fd_output = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    else
        data->fd_output = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
    if (data->fd_output == -1)
    {
        redir_error(file, data);
        return ;
    }
    free(file);
    dup2(data->fd_output, STDOUT);
}

void    input_redir(t_data *data, t_ASTNode *node)
{
    ft_close(data->fd_input);
    data->fd_input = open(node->left->content, O_RDONLY, S_IRWXU);
    if (data->fd_input == -1)
    {
        redir_error(node->left->content, data);
        return ;
    }
    dup2(data->fd_input, STDIN);
}
