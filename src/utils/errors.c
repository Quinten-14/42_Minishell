#include "../../include/minishell.h"
#include "../../include/libft.h"

void	throw_fatal(char *str, int exit_code)
{
	printf(ANSI_RED "%s\n" ANSI_RESET, str);
	exit(exit_code);
}

t_ASTNode	*ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (NULL);
}
