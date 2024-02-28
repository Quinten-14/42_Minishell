#include "../../include/minishell.h"
#include "../../include/libft.h"

// this one doesnt show exports with only var name and no value
// export without arguments does

int	env_command(t_env *env)
{
	if (!env)
		return (ERROR);
	while (env && env->next)
	{
		if (env->content != NULL)
			printf("%s=%s\n", env->var_name, env->content);
		env = env->next;
	}
	if (env && (env->content != NULL))
		printf("%s=%s\n", env->var_name, env->content);
	return (SUCCESS);
}
