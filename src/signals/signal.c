#include "../../include/minishell.h"
#include "../../include/libft.h"

void	handle_c(int num)
{
	(void)num;
	signal(SIGINT, handle_c);
	g_sig.ctrl_c = true;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_quit(int num)
{
	(void)num;
	//rl_on_new_line();
	//rl_redisplay();
}

t_ASTNode	*handle_d(t_data *data)
{
	ft_putendl_fd("exit ", 2);
	data->exit = true;
	return (NULL);
}

void	init_signal(void)
{
	g_sig.ctrl_c = false;
	g_sig.ctrl_d = false;
}
