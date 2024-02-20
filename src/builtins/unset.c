#include "../../include/minishell.h"

static int  unset_syntax(char *str)
{
    int i;

    if (ft_isdigit(str[0]))
        return (printf("Not a valid identifier\n"), 0);
    i = -1;
    while (str[++i])
        if (str[i] != '_' && !ft_isalnum(str[i]))
            return (printf("Not a valid identifier\n"), 0);
    return (0);
}

void    unset_command(t_env *env, char **strs)
{
    (void)env;
    int i;

    i = 1;
    while (strs[i])
    {
        unset_syntax(strs[i]);
        i++;
    }
}
