#include "../include/minishell.h"

// Main Logic Function

// Main Function
int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
    init_env_list(envp);
	while (data.exit == false)
	{
		input(&data);
	}
}
