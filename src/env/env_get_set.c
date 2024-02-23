#include "../../include/minishell.h"
#include "../../include/libft.h"

// function to get from env

char    *get_from_env(t_env *env, char *search)
{
    char    *path;

    while (env != NULL)
    {
        if (ft_strcmp(env->var_name, search) == 0)
        {
            path = ft_strdup(env->content);
            if (!path)
            {
                printf("Allocation Failed\n");
                exit(1);
                // throw fatal error
            }
            return (path);
        }
        env = env->next;
    }
    return (NULL);
}

void    create_env(t_env **env, char *var, char *update_val);

// function to update something in env

void    update_env(t_env *env, char *var, char *update_val)
{
    while (env)
    {
        if (ft_strcmp(env->var_name, var) == 0)
        {
            env->content = ft_strdup(update_val);
            if (env->content == NULL)
            {
                printf("Allocation Failed\n");
                exit(1);
                // throw fatal error
            }
            if (DEBUG_MODE)
                printf("%s Got Updated to %s\n", env->var_name, env->content);
            return ;
        }
        env = env->next;
    }
    // if the env doesnt exist you can create it
    create_env(&env, var, update_val);
}

void    create_env(t_env **env, char *var, char *update_val)
{   
    t_env   *new;
    t_env   *tmp;

    tmp = *env;
    while (tmp)
    {
        if (ft_strcmp(tmp->var_name, var) == 0)
        {
            update_env(tmp, var, update_val);
            return ;
        }
        tmp = tmp->next;
    }
    new = malloc(sizeof(t_env));
    if (!new)
    {
        printf("Allocation Failed\n");
        exit(1);
        // throw fatal error
    }
    new->var_name = ft_strdup(var);
    new->content = ft_strdup(update_val);
    new->next = *env;
    *env = new;
    if (DEBUG_MODE)
        printf("%s Created with value %s\n", new->var_name, new->content);
}
