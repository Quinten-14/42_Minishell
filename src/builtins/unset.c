#include "../../include/minishell.h"

static int  unset_syntax(char *str)
{
    int i;

    if (ft_isdigit(str[0]))
        return (printf("%s: Not a valid identifier\n", str), 0);
    i = -1;
    while (str[++i])
        if (str[i] != '_' && !ft_isalnum(str[i]))
            return (printf("%s: Not a valid identifier\n", str), 0);
    return (1);
}

static void delete_node(t_env **head, char *search) {
    t_env *current = *head;
    t_env *prev = NULL;

    if (current != NULL && strcmp(current->var_name, search) == 0) {
        *head = current->next;
        free(current->var_name);
        free(current->content);
        free(current);
        return;
    }
    while (current != NULL && strcmp(current->var_name, search) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    prev->next = current->next;
    free(current->var_name);
    free(current->content);
    free(current);
}

void    unset_command(t_env *env, char **strs)
{
    (void)env;
    int i;

    i = 1;
    while (strs[i])
    {
        if (unset_syntax(strs[i]) == 1)
            delete_node(&env, strs[i]);
        i++;
    }
}
