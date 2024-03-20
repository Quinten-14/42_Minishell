#include "../../include/libft.h"
#include "../../include/minishell.h"

// this one doesnt show exports with only var name and no value
// export without arguments does

int	env_command(t_env *env)
{
	if (!env)
		return (ERROR);
	while (env && env->next)
	{
		if (env->content != NULL && ft_strcmp(env->content,
				"-NULL-EMPTY-") != 0)
			printf("%s=%s\n", env->var_name, env->content);
		env = env->next;
	}
	if (env && (env->content != NULL && ft_strcmp(env->content,
				"-NULL-EMPTY-") != 0))
		printf("%s=%s\n", env->var_name, env->content);
	return (SUCCESS);
}
