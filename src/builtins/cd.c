#include "../../include/minishell.h"

/* CD Basics */

/*
 * When Doing CD it should bring you back to the home path
 * When Doing CD - it should bring you to the OLDPWD
 * You can use both relative and absolute paths
 * We need to update OLDPWD and PWD environment variables
 * If minishell started and no OLDPWD set it should give a error message -
 * when doing CD -
 */

// function to create or update oldpwd
static void	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	while (env != NULL && (ft_strcmp(env->var_name, "OLDPWD") != 0))
	{
		if (env->next == NULL)
		{
			add_node(&env, ft_strjoin("OLDPWD=", cwd));
			return ;
		}
		env = env->next;
	}
	env->content = ft_strdup(cwd);
	if (env->content == NULL)
	{
		// needs to be changed in correct error handler
		printf("Allocation Failed\n");
		exit(1);
	}
}

static void	update_pwd(t_env *env)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	while (env != NULL && (ft_strcmp(env->var_name, "PWD") != 0))
		env = env->next;
	env->content = ft_strdup(cwd);
	if (env->content == NULL)
	{
		// needs to be changed in correct error handler
		fprintf(stderr, "Allocation Failed\n");
		exit(1);
	}
}

static char	*get_from_env(t_env *env, char *search)
{
	char	*path;

	while (env != NULL)
	{
		if (ft_strcmp(env->var_name, search) == 0)
		{
			path = ft_strdup(env->content);
			if (path == NULL)
			{
				fprintf(stderr, "Allocation Failed\n");
				exit(1);
			}
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

void	cd_command(char **strs, t_env *env)
{
	char	*path;

	if (strs[2] != NULL)
	{
		printf("Too many arguments\n");
		return ;
	}
	if (strs[1] == NULL)
		path = get_from_env(env, "HOME");
	else if (ft_strcmp(strs[1], "~") == 0)
		path = get_from_env(env, "HOME");
	else if (ft_strcmp(strs[1], "-") == 0)
		path = get_from_env(env, "OLDPWD");
	else if (strs[1][0] == '~' && strs[1][1] == '/')
		path = ft_strjoin(get_from_env(env, "HOME"), strs[1] + 1);
	else
	{
		path = strs[1];
	}
	update_oldpwd(env);
	//if (chdir(path) == 0)
	//	update_pwd(env);
	//else
	//	perror("chdir");
	if (chdir(path) < 0)
		return ((void)perror("chdir"));
	update_pwd(env);
}
