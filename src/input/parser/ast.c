#include "../../../include/minishell.h"
#include "../../../include/libft.h"

t_ASTNode	*create_ast(char *content, int *element);
t_ASTNode	*add_node(t_input *input, t_ASTNode *current, int *element);
t_input		*destroy_node(t_input *input);
t_ASTNode	*parse_to_ast(t_input *input);
void	free_input(t_input *input);

t_input	*traverse_input(t_input *input, int *element)
{
	if (ft_strcmp(input->type, "pipe") == 0)
		return (NULL);
	while (input->next != NULL)
	{
		(*element)++;
		input = input->next;
	}
	if (ft_strcmp(input->type, "pipe") == 0)
		return (NULL);
	while ((input->prev != 0) && (ft_strcmp(input->type, "pipe") != 0))
		input = input->prev;
	return (input);
}

t_ASTNode	*build_ast(t_input *input, int element)
{
	t_ASTNode	*head;
	t_ASTNode	*curr;

	head = create_ast(input->content, &element);
	curr = head;
	ft_printf("\thead node = %s\n", head->content);
	input = input->next;
	while (element != 0)
	{
		while (input->next != NULL)
		{
			curr = add_node(input, curr, &element);
			input = input->next;
		}
		curr = add_node(input, curr, &element);
		while ((curr->parent != 0) && (ft_strcmp(curr->content, "|")) != 0)
		{
			ft_printf("---UP---\n");
			curr = curr->parent;
		}
		while ((input->prev != 0) && (ft_strcmp(input->type, "pipe") != 0))
			input = destroy_node(input);
		if ((ft_strcmp(input->type, "pipe") == 0) || (!input->prev))
			input = destroy_node(input);
		if (element == 0)
			break ;
		while ((input->prev != 0) && (ft_strcmp(input->type, "pipe") != 0))
			input = input->prev;
	}
	return (head);
}

t_ASTNode	*parse_to_ast(t_input *input)
{
	t_ASTNode	*head;
	int			element;

	element = 1;
	input = traverse_input(input, &element);
	if (!input)
		return (NULL);
	head = build_ast(input, element);
	if (!head->left && !head->right)
		input = destroy_node(input);
	if (!head)
		return (NULL);
	return (head);
}

