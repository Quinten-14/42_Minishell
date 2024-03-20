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

void	sigint_handler_in_process(int sig)
{
	(void) sig;
	write(1, "\n", 1);
}

void sigint_handler(int sig)
{
    (void)sig;
    if (g_sig.here_doc_pid > 0)
    {
        // Terminate the child process
        kill(g_sig.here_doc_pid, SIGTERM);
        // Delete the temporary file
        unlink("/tmp/here_doc");
        // Set the here_doc_interrupted variable to true
        g_sig.abort_exec = true;
    }
    else
    {
        // If not in here_doc, print a newline
        write(STDOUT_FILENO, "\n", 1);
    }
}

void	sigquit_handler_in_process(int sig)
{
	(void) sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

t_ASTNode	*handle_d(t_data *data)
{
	if (!g_sig.in_heredoc)
	{
	ft_putendl_fd("exit ", 2);
	data->exit = true;
	}
	return (NULL);
}

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, handle_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 2)
	{
		signal(SIGINT, sigint_handler_in_process);
		signal(SIGQUIT, sigquit_handler_in_process);
	}
	else if (sig == 3)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler_in_process);
	}
}
