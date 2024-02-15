#include "../../include/minishell.h"

int put_env(t_env *env)
{
    while (env && env->next)
    {
        printf("%s\n", env->content);
        env = env->next;
    }
    if (env)
        printf("%s\n", env->content);
    return (SUCCESS);
}
