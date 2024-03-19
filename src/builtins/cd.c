#include "../../include/minishell.h"
#include "../../include/libft.h"

/*
void	cd_command(char **strs, t_env *env)
{
	char	*path;

	if (strs[1] != NULL && strs[2] != NULL)
		return ((void)printf("Too many arguments\n"));
	if (strs[1] != NULL && (strs[1][0] == '-' && strs[1][1]))
	{
		return ((void)printf("Flags are not supported\n"));
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
	update_env(&env, "OLDPWD", get_from_env(env, "PWD"));
	if (chdir(path) < 0)
		return ((void)perror("cd"));
	update_env(&env, "PWD", getcwd(NULL, 0));
}
*/

void cd_command(char **strs, t_env *env)
{
    char *path = NULL;
    if (strs[1] != NULL && strs[2] != NULL)
    {
        printf("Too many arguments\n");
        return;
    }
    if (strs[1] != NULL && (strs[1][0] == '-' && strs[1][1]))
    {
        printf("Flags are not supported\n");
        return;
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
        path = ft_strdup(strs[1]);

    if (!path)
    {
        perror("cd");
        return;
    }
    char *old_pwd = get_from_env(env, "PWD");
    update_env(&env, "OLDPWD", old_pwd);
    if (chdir(path) < 0)
    {
        perror("cd");
        free(path);
        free(old_pwd);
        return;
    }
    char *new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
    {
        perror("cd");
        free(path);
        free(old_pwd);
        return;
    }
    update_env(&env, "PWD", new_pwd);
    free(path);
    free(old_pwd);
    free(new_pwd);
}

