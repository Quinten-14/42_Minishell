#include "../../include/minishell.h"
#include "../../include/libft.h"

int	get_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
	return (ERROR);
}
