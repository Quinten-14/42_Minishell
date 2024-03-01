#include "../include/minishell.h"

t_signal	g_sig;
// Main Logic Function

// Main Function
int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_ASTNode	*head;

	signal(SIGINT, handle_c);
	signal(SIGQUIT, handle_d);
	(void)ac;
	(void)av;
	init_signal();
	data.exit = false;
	data.env_list = *init_env_list(envp);
	while (data.exit == false && g_sig.ctrl_d == false)
	{
		head = input(&data);
		if (head)
			command_executor(head, &data);
	}
	if (data.exit == true || g_sig.ctrl_d == true)
	{
		//free_env_list(&data.env_list);
	}
	return (data.ret);
}
