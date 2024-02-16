#include "../../include/minishell.h"

int put_env(t_env *env)
{
    while (env && env->next)
    {
        printf("%s=%s\n", env->var_name, env->content);
        env = env->next;
    }
    if (env)
        printf("%s=%s\n", env->var_name, env->content);
    return (SUCCESS);
}
