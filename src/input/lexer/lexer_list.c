#include "../../../include/minishell.h"

char	*check_types(char *str, int i, char **arr);

t_input	*new_list(char *str, int i, char **arr)
{
	t_input	*new;

	new = malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	new->content = str;
	new->type = check_types(str, i, arr);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// still need protection for if new list fails
void	add_node_input(t_input **head, char *str, int i, char **arr)
{
	t_input	*new_node;
	t_input	*current;

	new_node = new_list(str, i, arr);
    if (!new_node)
	{
        return ;
	}
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
		new_node->prev = current;
	}
}

void	print_list(t_input *head)
{
	t_input	*current;

	current = head;
	while (current != NULL)
	{
		printf("Content: %s, Type: %s\n", current->content, current->type);
		current = current->next;
	}
}
