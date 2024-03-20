#include "../../include/get_next_line.h"
#include "../../include/libft.h"
#include "../../include/minishell.h"
#include <sys/fcntl.h>
#include <sys/stat.h>

/* Helper function to throw the redirection error */

void	redir_error(char *file, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(file, STDERR);
	ft_putendl_fd(": No such file or directory", STDERR);
	data->ret = 1;
	data->abort_exec = true;
}

/* Redir will be called if > or >> are the redirection needed */

void	redir(t_data *data, t_ASTNode *node)
{
	char	*file;

	if (!node->left)
	{
		data->abort_exec = true;
		data->ret = 1;
		return ;
	}
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

void	input_redir(t_data *data, t_ASTNode *node)
{
	if (!node->left)
	{
		data->abort_exec = true;
		data->ret = 1;
		return ;
	}
	ft_close(data->fd_input);
	data->fd_input = open(node->left->content, O_RDONLY, S_IRWXU);
	if (data->fd_input == -1)
	{
		redir_error(node->left->content, data);
		return ;
	}
	dup2(data->fd_input, STDIN);
}

static void	write_to_temp_file(int fd, t_ASTNode *node)
{
	char	*line;
	char	*trimmed;

	while (g_sig.in_heredoc == false)
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			trimmed = ft_strtrim(line, "\n");
			if (ft_strcmp(trimmed, node->left->content) == 0)
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, fd);
			free(line);
			free(trimmed);
		}
	}
	free(trimmed);
	get_next_line(-1);
}

char	*here_doc(t_data *data, t_ASTNode *node)
{
	char	*file;
	int		fd;

	run_signals(3);
	if (!node->left)
	{
		data->abort_exec = true;
		data->ret = 1;
		return (NULL);
	}
	file = "/tmp/here_doc";
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		return (redir_error(file, data), NULL);
	write_to_temp_file(fd, node);
	ft_close(fd);
	return (ft_strdup(file));
}
