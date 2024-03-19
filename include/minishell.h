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
# include <sys/types.h>
# include <sys/wait.h>
# include "./data.h"
# include "./functions.h"

/* Defines Section */

# ifndef DEBUG_MODE
#  define DEBUG_MODE false
# endif

/* Colors */
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_WHITE   "\x1b[37m"
#define ANSI_RESET   "\x1b[0m"

/* Global Variable */

extern t_signal	g_sig;

#endif
