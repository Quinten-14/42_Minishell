#include "../../include/libft.h"
#include "../../include/minishell.h"
#include <sys/wait.h>
#include <unistd.h>

// if i make a hero doc i should make it so it is in a child process.
// this way it is easier to handle the signals

char	*get_path(char *cmd, t_env *env)
{
	char	*path;
	char	*exec_path;
	char	**allpath;
	char	*path_part;
	char	*exec;
	int		i;

	path = get_from_env(env, "PATH");
	exec_path = NULL;
	if (path)
	{
		allpath = ft_split(path, ':');
		free(path);
		i = -1;
		while (allpath[++i])
		{
			path_part = ft_strjoin(allpath[i], "/");
			exec = ft_strjoin(path_part, cmd);
			free(path_part);
			if (access(exec, F_OK | X_OK) == 0)
			{
				exec_path = exec;
				break ;
			}
			free(exec);
		}
		free_array(allpath);
	}
	if (!exec_path)
		return (NULL);
	return (exec_path);
}

int	run_binary(char *cmd, t_data *data, char **argv)
{
	pid_t	pid;
	int		status;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (ft_strchr(cmd, '/') != NULL)
			execve(cmd, argv, data->env);
		else
		{
			path = get_path(cmd, data->env_list);
			if (path)
				execve(path, argv, data->env);
		}
		perror("Error executing binary");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(data->pipe_in);
		close(data->pipe_out);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (EXIT_FAILURE);
	}
}
