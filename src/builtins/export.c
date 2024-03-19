#include "../../include/minishell.h"
#include "../../include/libft.h"

static int	print_exports(t_env *env)
{
	if (!env)
		return (ERROR);
	while (env && env->next)
	{
		if (env->content != NULL && ft_strcmp(env->content, "-NULL-EMPTY-") != 0)
			printf("declare -x %s=\"%s\"\n", env->var_name, env->content);
		else
			printf("declare -x %s\n", env->var_name);
		env = env->next;
	}
	if (env)
	{
		if (env->content != NULL && ft_strcmp(env->content, "-NULL-EMPTY-") != 0)
			printf("declare -x %s=\"%s\"\n", env->var_name, env->content);
		else
			printf("declare -x %s\n", env->var_name);
	}
	return (SUCCESS);
}

static int	export_syntax(char *str)
{
	int	i;

	if (ft_isdigit(str[0]))
		return (printf("%s: Not a valid identifier\n", str), 0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (printf("%s: not a valid identifier\n", str), 0);
		i++;
	}
	return (1);
}

static void	handle_export(char *str, t_env *env)
{
	size_t	i;
	size_t	j;
	char	*substr;
	char	*new_value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = i;
	if (str[i] == '=')
		i++;
	substr = ft_substr(str, 0, j);
	if (!substr)
		throw_fatal("Allocation Failed", 1);
	if (ft_strlen(str) == j)
		new_value = "-NULL-EMPTY-";
	else
		new_value = ft_substr(str, i, (ft_strlen(str) - i));
	if (!new_value && ft_strlen(str) != j)
		throw_fatal("Allocation Failed", 1);
	if (var_exists(env, substr) && ft_strcmp(new_value, "-NULL-EMPTY-") == 0)
		return ;
	if (get_from_env(env, substr) != NULL && ft_strcmp(new_value, "-NULL-EMPTY-") == 0)
		return ;
	if (DEBUG_MODE)
		printf("exporting %s\n", substr);
	update_env(&env, substr, new_value);
    free(substr);
    free(new_value);
}

void	export_command(char **strs, t_env *env)
{
	int	i;

	if (!strs[1])
		print_exports(env);
	i = 1;
	while (strs[i])
	{
		if (export_syntax(strs[i]))
			handle_export(strs[i], env);
		i++;
	}
}
