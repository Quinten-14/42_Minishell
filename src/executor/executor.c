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

void    execute_pipe(t_ASTNode *node, t_data *data)
{
    int     pipefd[2];
    pid_t   pid;
    int     status;
    int     saved_stdout;
    int     saved_stdin;

    saved_stdout = dup(STDOUT);
    saved_stdin = dup(STDIN);

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        dup2(pipefd[1], STDOUT);
        close(pipefd[0]);
        if (ft_strcmp(node->left->type, "pipe") == 0)
        {
            execute_pipe(node->left, data);
        }
        else
        {
            command_executor(node->left, data);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        dup2(pipefd[0], STDIN);
        close(pipefd[1]);
        command_executor(node->right, data);
        waitpid(pid, &status, 0); // Wait for the specific child process to finish
    }

    dup2(saved_stdout, STDOUT);
    close(saved_stdout);
    dup2(saved_stdin, STDIN);
    close(saved_stdin);
}

void    command_executor(t_ASTNode *node, t_data *data)
{
    char    **args;
    int     saved_stdout;
    int     saved_stdin;

    saved_stdout = dup(STDOUT);
    saved_stdin = dup(STDIN);

    if (node->right && (ft_strcmp(node->right->type, "great") == 0 || ft_strcmp(node->right->type, "dgreat") == 0))
        redir(data, node->right);
    if (node->right && ft_strcmp(node->right->type, "less") == 0)
        input_redir(data, node->right);
    args = arg_arr(node);
    if (args && ft_strcmp(node->content, "exit") == 0 && has_pi(node) == false)
        exit_command(data, args);
    else if (args && is_builtin(node->content))
        data->ret = exec_builtin(node->content, args, data);
    else if (args)
        data->ret = run_binary(node->content, data, args);
    // free args
    ft_close(data->pipe_in);
    ft_close(data->pipe_out);
    data->pipe_in = -1;
    data->pipe_out = -1;

    dup2(saved_stdout, STDOUT);
    close(saved_stdout);
    dup2(saved_stdin, STDIN);
    close(saved_stdin);
}
