#include "../include/minishell.h"
#include "../include/libft.h"

t_signal	g_sig;
// Main Logic Function

// env list to array
char	**env_list_to_array(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	int		i;
    char    *tmp_str;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
        tmp_str = ft_strjoin(tmp->var_name, "=");
        if (!tmp_str)
        {
            while (i > 0)
                free(envp[--i]);
            free(envp);
            return NULL;
        }
        envp[i] = ft_strjoin(tmp_str, tmp->content);
        free(tmp_str);
        if (!envp[i])
        {
            while (i > 0)
                free(envp[--i]);
            free(envp);
            return NULL;
        }
        tmp = tmp->next;
        i++;
	}
	envp[i] = NULL;
	return (envp);
}

void    free_env_array(char **env)
{
    int i;

    i = 0;
    if (!env)
        return ;
    while (env[i] != NULL)
    {
        free(env[i]);
        i++;
    }
    free(env);
}

// Main Function
int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_ASTNode	*head;

	g_sig.in_child = false;
	(void)ac;
	(void)av;
	reset_fds(&data);
	init_data(&data, envp);
	data.env_list = init_env_list(envp);
	increment_shell_lvl(data.env_list);
	while (data.exit == false)
	{
		run_signals(1);
		data.env = env_list_to_array(data.env_list);
		head = input(&data);
		if (head)
		{
			executor(head, &data);
			free_ast(head);
		}
        free_env_array(data.env);
	}
	if (data.exit == true)
		free_env_list(data.env_list);
	return (data.ret);
}
