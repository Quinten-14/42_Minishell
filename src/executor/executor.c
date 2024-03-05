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
int	command_executor(t_ASTNode *node, t_data *data)
{
	char	**args;

	args = arg_arr(node);
	if (is_builtin(node->content))
		return (exec_builtin(node->content, args, data));
	else if (get_path(node->content, &data->env_list) != NULL)
		run_binary(node->content, data, args);
	else
		printf("Command not found\n");
	return (1);
}
