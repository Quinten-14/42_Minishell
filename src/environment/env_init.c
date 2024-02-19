#include "../../include/minishell.h"
#include "../../include/libft.h"
#include <string.h>

// maybe needs a different split that only splits at first =
static t_env    *new_list(char *content)
{
    t_env   *env;
    char    **vars;

    vars = ft_split(content, '=');
    env = malloc(sizeof(t_env));
    if (!env)
        return (NULL);
    env->content = vars[1];
    env->var_name = vars[0];
    env->next = NULL;
    env->exported = true;
    return (env);
}

void add_node(t_env **head, char *content)
{
    t_env   *new;
    t_env   *current;

    new = new_list(content);
    if (*head == NULL)
        *head = new;
    else
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new;
    }
}

static void print_list(t_env *head, bool exported_only)
{
    t_env   *curr;

    curr = head;
    while (curr != NULL)
    {
        if (curr->exported == exported_only)
            printf("env var_name: %s\nenv content: %s\n", curr->var_name, curr->content);
        curr = curr->next;
    }
    printf("\nAll Environment Variables Loaded In\n\n");
}

t_env   *init_env_list(char **envp)
{
    t_env   *environment;
    int i;

    environment = new_list(envp[0]);
    i = 0;
    while (envp[i])
    {
        if (!(strncmp(envp[i], "OLDPWD", 6) == 0))
            add_node(&environment, envp[i]);
        i++;
    }
    if (DEBUG_MODE == true)
        print_list(environment, true);
    printf("OLDPWD Exists: %d\n", node_exists("OLDPWD", &environment));
    return (environment);
}
