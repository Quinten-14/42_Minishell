#include "../../../include/minishell.h"
#include "../../../include/libft.h"

void	free_input(t_input *input);

void	free_ast(t_ASTNode *head)
{
	if (!head)
		return ;
	free_ast(head->left);
	free_ast(head->right);
	free(head->content);
	free(head->type);
	free(head);
}

t_ASTNode	*create_ast(t_input *input, int *element)
{
	t_ASTNode	*head;

	head = malloc(sizeof(t_ASTNode));
	if (!head)
		return (NULL);
	head->parent = NULL;
	head->left = NULL;
	head->right = NULL;
	head->content = ft_strdup(input->content);
	head->type = ft_strdup(input->type);
	(*element)--;
	return (head);
}

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

	head = create_ast(input, &element);
	curr = head;
	if (DEBUG_MODE)
		printf("\thead node: content = %s, type = %s\n", head->content, head->type);
	input = input->next;
	while (element != 0)
	{
		while (input->next != NULL)
		{
			curr = add_ast_node(input, curr, &element);
			input = input->next;
		}
		curr = add_ast_node(input, curr, &element);
		while ((curr->parent != 0) && (ft_strcmp(curr->content, "|")) != 0)
		{
			if (DEBUG_MODE)
				printf("---UP---\n");
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
