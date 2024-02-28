#include "../../../include/minishell.h"
#include "../../../include/libft.h"

char	*check_types(char *str, int i, char **arr);

t_input	*new_list(char *str, int i, char **arr)
{
	t_input	*new;

	new = malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	new->content = ft_strdup(str);
	new->type = check_types(str, i, arr);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_input	*destroy_node(t_input *input)
{
	t_input	*tmp;

	if (!input->prev)
	{
		tmp = NULL;
		free(input->content);
		free(input);
		return (NULL);
	}
	tmp = input->prev;
	tmp->next = NULL;
	free(input->content);
	free(input);
	return (tmp);
}

void	free_input(t_input *input)
{
	while (input->next != NULL)
		input = input->next;
	while (input)
		input = destroy_node(input);
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
