#include "../../include/minishell.h"

int   node_exists(char *str, t_env **head)
{
    t_env *current;

    current = *head;
    while (current->next != NULL)
    {
        if (ft_strcmp(str, current->var_name) == 0)
            return (1);
        current = current->next;
    }
    return (0);
}

// function to reset the oldpwd if there is one when minishell started
/*
void    reset_oldpwd(t_env **head)
{
    t_env   *prev;
    t_env   *next;
    t_env   *current;

    if (find_node("OLDPWD", head))
        return ;
}
*/
