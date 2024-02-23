#include "../../include/minishell.h"

int env_command(t_env *env)
{
    if (!env)
        return (ERROR);
    while (env && env->next)
    {
        printf("%s=%s\n", env->var_name, env->content);
        env = env->next;
    }
    if (env)
        printf("%s=%s\n", env->var_name, env->content);
    return (SUCCESS);
}
