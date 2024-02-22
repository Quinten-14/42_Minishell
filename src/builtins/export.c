#include "../../include/minishell.h"

static int    export_env(t_env *env)
{
    while (env && env->next)
    {
        printf("declare -x %s=%s\n", env->var_name, env->content);
        env = env->next;
    }
    if (env)
        printf("declare -x %s=%s\n", env->var_name, env->content);
    return (SUCCESS);
}

static int export_syntax(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
    {
        if (ft_isdigit(str[0]))
            return (0);
        if (str[i] != '_' && !ft_isalnum(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void    handle_export(t_env *env, char *str)
{

}

void    export_command(t_env *env, char **strs)
{
    int i;

    i = 1;
    if (array_len(strs) == 1)
        return ((void)export_env(env));
    while (strs[i])
    {
        if (export_syntax(strs[i]))
            handle_export(env, strs[i]);
        else
            printf("%s: Not a valid identifier\n", strs[i]);
        i++;
    }
}
