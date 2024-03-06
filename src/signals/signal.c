#include "../../include/minishell.h"
#include "../../include/libft.h"

void	handle_c(int num)
{
	(void)num;
	if (g_sig.in_child == true)
		signal(SIGINT, SIG_DFL);
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_quit(int num)
{
	(void)num;
	if (g_sig.in_child == true)
		signal(SIGQUIT, SIG_DFL);
	else
		signal(SIGQUIT, SIG_IGN);
}

t_ASTNode	*handle_d(t_data *data)
{
	ft_putendl_fd("exit ", 2);
	data->exit = true;
	return (NULL);
}
