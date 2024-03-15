#include "../../include/minishell.h"
#include "../../include/libft.h"

void	handle_c(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_quit(int num)
{
	(void)num;
	signal(SIGQUIT, SIG_IGN);
}

t_ASTNode	*handle_d(t_data *data)
{
	ft_putendl_fd("exit ", 2);
	data->exit = true;
	return (NULL);
}
