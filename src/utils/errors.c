#include "../../include/minishell.h"

void	throw_fatal(char *str, int exit_code)
{
	printf("%s\n", str);
	exit(exit_code);
}
