#include "../../include/libft.h"
#include "../../include/minishell.h"

// my executor takes in a abstract syntax tree. my first command is the most to the left bottom of the tree.
// redirects are on the right side of the nodes and arguments are on the left side of the nodes.

// on the left side of the node are the arguments.
// on the right side of the node are the redirects.
// on the left side of the redirect node is the file to redirect to.

bool	is_builtin(char *command);
int		exec_builtin(char *cmd, char **args, t_data *data);
int		amount_args(t_ASTNode *head);
char	**arg_arr(t_ASTNode *node);
char	*get_path(char *cmd, t_env *env);
// execute the command

bool    has_pi(t_ASTNode *node)
{
    t_ASTNode *tmp;

    tmp = node;
    while (tmp)
    {
        if (ft_strcmp(tmp->content, "|") == 0)
            return (true);
        tmp = tmp->right;
    }
    return (false);
}

void    command_executor(t_ASTNode *node, t_data *data)
{
    char    **args;

    args = arg_arr(node);
    data->cont = true; // for now
    if (data->cont == false)
        return ;
    if (args && ft_strcmp(node->content, "exit") == 0 && has_pi(node) == false)
        exit_command(data, args);
    else if (args && is_builtin(node->content))
        data->ret = exec_builtin(node->content, args, data);
    else if (args)
    {
        printf("is binary\n");
        data->ret = run_binary(node->content, data, args);
    }
    // free args
    ft_close(data->pipe_in);
    ft_close(data->pipe_out);
    data->pipe_in = -1;
    data->pipe_out = -1;
    data->cont = false;
}
