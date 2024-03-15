#include "../../include/minishell.h"
#include "../../include/libft.h"
#include "../../include/get_next_line.h"
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

char	*here_doc(t_data *data, t_ASTNode *node)
{
	char	*file;
	char	*line;
	int		fd;

	if (!node->left)
	{
		data->abort_exec = true;
		data->ret = 1;
		return (NULL);
	}
	file = "/tmp/here_doc";
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		redir_error(file, data);
		return (NULL);
	}
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strcmp(ft_strtrim(line, "\n"), node->left->content) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	return (ft_strdup(file));
}
