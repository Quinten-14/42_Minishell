#include "../../include/libft.h"
#include "../../include/minishell.h"

static t_input	*new_list(char *str, int i, char **arr)
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
static void	add_node_doubly(t_input **head, char *str, int i, char **arr)
{
	t_input	*new_node;
	t_input	*current;

	new_node = new_list(str, i, arr);
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

static void	print_list(t_input *head)
{
	t_input	*current;

	current = head;
	while (current != NULL)
	{
		printf("Content: %s, Type: %s\n", current->content, current->type);
		current = current->next;
	}
}

t_input	*lexer(char *prompt)
{
	char	**splitted;
	t_input	*input_list;
	int		i;

	splitted = ft_split(prompt, ' ');
	input_list = new_list(splitted[0], 0, splitted);
	i = 1;
	while (splitted[i])
	{
		add_node_doubly(&input_list, splitted[i], i, splitted);
		i++;
	}
	if (DEBUG_MODE == true)
		print_list(input_list);
    return (input_list);
}
