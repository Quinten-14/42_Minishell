#include "../../include/minishell.h"

void	handle_c(int num)
{
	(void)num;
	g_sig.ctrl_c = true;
}

void	handle_d(int num)
{
	g_sig.ctrl_d = true;
	printf("%d\n", num);
}

void    init_signal(void)
{
    g_sig.ctrl_c = false;
    g_sig.ctrl_d = false;
}