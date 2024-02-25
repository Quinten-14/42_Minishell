#include "../../include/libft.h"
#include "../../include/minishell.h"

static t_env	*new_list(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->content = value;
	env->var_name = name;
	env->next = NULL;
	env->exported = true;
	return (env);
}

void	add_node_create(t_env **head, char *name, char *value)
{
	t_env	*new;
	t_env	*current;

	new = new_list(name, value);
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