#include "../include/minishell.h"

t_signal	g_sig;
// Main Logic Function

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
	init_data(&data, envp);
	data.env_list = init_env_list(envp);
	while (data.exit == false)
	{
		head = input(&data);
		if (head)
		{
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
