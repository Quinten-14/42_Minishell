#include "../../include/libft.h"
#include "../../include/minishell.h"

bool	is_builtin(char *command);
int		exec_builtin(char *cmd, char **args, t_data *data);
int		amount_args(t_ASTNode *head);
char	**arg_arr(t_ASTNode *node);
char	*get_path(char *cmd, t_env *env);
bool	has_pi(t_ASTNode *node);
void	handle_abort_exec(int saved_stdout, int saved_stdin);

void	handle_here_doc(t_ASTNode *node, t_data *data)
{
	char	*here_doc_file;
	int		fd;

	here_doc_file = NULL;
	if (node->right && ft_strcmp(node->right->type, "here_doc") == 0)
		here_doc_file = here_doc(data, node->right);
	if (here_doc_file != NULL)
	{
		fd = open(here_doc_file, O_RDONLY);
		if (fd != -1)
		{
			dup2(fd, STDIN);
			ft_close(fd);
		}
		free(here_doc_file);
	}
}

void	execute_pipe(t_ASTNode *node, t_data *data)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		saved_stdout;
	int		saved_stdin;

	saved_stdout = dup(STDOUT);
	saved_stdin = dup(STDIN);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT);
		close(pipefd[0]);
		if (ft_strcmp(node->left->type, "pipe") == 0)
			execute_pipe(node->left, data);
		else
			command_executor(node->left, data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		dup2(pipefd[0], STDIN);
		close(pipefd[1]);
		if (node->right && ft_strcmp(node->right->type, "here_doc") == 0)
			handle_here_doc(node->right, data);
		command_executor(node->right, data);
		waitpid(pid, &status, 0);
	}
	dup2(saved_stdout, STDOUT);
	ft_close(saved_stdout);
	dup2(saved_stdin, STDIN);
	ft_close(saved_stdin);
}

void	command_executor(t_ASTNode *node, t_data *data)
{
	char	**args;
	int		saved_stdout;
	int		saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	data->abort_exec = false;
	if (node->right && (ft_strcmp(node->right->type, "great") == 0
			|| ft_strcmp(node->right->type, "dgreat") == 0))
		redir(data, node->right);
	if (node->right && ft_strcmp(node->right->type, "less") == 0)
		input_redir(data, node->right);
	if (data->abort_exec)
		return ((void)handle_abort_exec(saved_stdout, saved_stdin));
	handle_here_doc(node, data);
	if (data->abort_exec)
		return ((void)handle_abort_exec(saved_stdout, saved_stdin));
	args = arg_arr(node);
	if (args && ft_strcmp(node->content, "exit") == 0 && has_pi(node) == false)
		exit_command(data, args);
	else if (args && is_builtin(node->content))
		data->ret = exec_builtin(node->content, args, data);
	else if (args)
		data->ret = run_binary(node->content, data, args);
    free(args);
	dup2(saved_stdout, STDOUT);
	ft_close(saved_stdout);
	dup2(saved_stdin, STDIN);
	ft_close(saved_stdin);
}

void	executor(t_ASTNode *node, t_data *data)
{
	run_signals(2);
	if (ft_strcmp(node->type, "pipe") == 0)
		execute_pipe(node, data);
	else
		command_executor(node, data);
}
