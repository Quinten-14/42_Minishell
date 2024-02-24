#include "../../include/minishell.h"
#include "../../include/libft.h"

static int  unset_syntax(char *str)
{
    int i;

    if (ft_isdigit(str[0]))
        return (printf("%s: Not a valid identifier\n", str), 0);
    i = -1;
    while (str[++i])
        if (str[i] != '_' && !ft_isalnum(str[i]))
            return (printf("%s: Not a valid identifier\n", str), 0);
    return (1);
}

void    unset_command(t_env *env, char **strs)
{
    (void)env;
    int i;

    i = 1;
    while (strs[i])
    {
        if (unset_syntax(strs[i]) == 1)
            delete_env(&env, strs[i]);
        i++;
    }
}
