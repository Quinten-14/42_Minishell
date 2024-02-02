#include "../../include/minishell.h"
#include "../../include/libft.h"

// Mostly test code and needs to be changed a lot still maybe

int get_pwd(void)
{
    char    cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX))
    {
        ft_putendl_fd(cwd, 1);
        return (0);
    }
    // throw error
    return (1);
}
