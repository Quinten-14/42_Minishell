#include "../include/minishell.h"

// Main Logic Function

// Main Function
int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	data.exit = false;
	data.env_list = *init_env_list(envp);
	while (data.exit == false)
	{
		input(&data);
	}
	if (data.exit == true)
	{
		//free_env_list(&data.env_list);
	}
	return (data.ret);
}
