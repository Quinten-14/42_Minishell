#include "../include/minishell.h"
#include "../include/libft.h"

t_signal	g_sig;
// Main Logic Function

// env list to array
char	**env_list_to_array(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->var_name, "=");
		envp[i] = ft_strjoin(envp[i], tmp->content);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

// Main Function
int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_ASTNode	*head;

	g_sig.in_child = false;
	signal(SIGINT, handle_c);
	signal(SIGQUIT, SIG_IGN);
	(void)ac;
	(void)av;
    reset_fds(&data);
	init_data(&data, envp);
	data.env_list = init_env_list(envp);
    increment_shell_lvl(data.env_list);
	while (data.exit == false)
	{
		data.env = env_list_to_array(data.env_list);
		head = input(&data);
		if (head)
		{
			if (ft_strcmp(head->type, "pipe") == 0)
				execute_pipe(head, &data);
			else
				command_executor(head, &data);
			free_ast(head);
		}
	}
	if (data.exit == true)
	{
		free_env_list(data.env_list);
	}
	return (data.ret);
}
