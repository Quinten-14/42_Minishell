#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes Section */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include "./data.h"
# include "./functions.h"

/* Defines Section */

# ifndef DEBUG_MODE
#  define DEBUG_MODE false
# endif

extern t_signal	g_sig;

#endif
