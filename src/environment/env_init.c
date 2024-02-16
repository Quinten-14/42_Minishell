#include "../../include/minishell.h"

static t_env    *new_list(char *content)
{
    t_env   *env;

    env = malloc(sizeof(t_env));
    if (!env)
        return (NULL);
    env->content = content;
    env->next = NULL;
    return (env);
}

static void add_node(t_env **head, char *content)
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

static void print_list(t_env *head)
{
    t_env   *curr;

    curr = head;
    while (curr != NULL)
    {
        printf("environment content: %s\n", curr->content);
        curr = curr->next;
    }
}

t_env   *init_env_list(char **envp)
{
    t_env   *environment;
    int i;

    environment = new_list(envp[0]);
    i = 0;
    while (envp[i])
    {
        add_node(&environment, envp[i]);
        i++;
    }
    if (DEBUG_MODE == true)
        print_list(environment);
    return (environment);
}
