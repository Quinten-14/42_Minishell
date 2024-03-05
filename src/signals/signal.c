#include "../../include/minishell.h"
#include "../../include/libft.h"

void	handle_c(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

t_ASTNode	*handle_d(t_data *data)
{
	ft_putendl_fd("exit ", 2);
	data->exit = true;
	return (NULL);
}

