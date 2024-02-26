/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-paep <lde-paep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:44:52 by lde-paep          #+#    #+#             */
/*   Updated: 2024/02/26 14:55:33 by lde-paep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_ASTNode	*create_ast(char *content, int *element)
{
	t_ASTNode	*head;

	head = malloc(sizeof(t_ASTNode));
	if (!head)
		return (NULL);
	head->parent = NULL;
	head->left = NULL;
	head->right = NULL;
	head->content = ft_strdup(content);
	(*element)--;
	return (head);
}

t_ASTNode	*add_left_node(t_ASTNode *parent, char *content, int *element)
{
	t_ASTNode	*new_node;

	new_node = malloc(sizeof(t_ASTNode));
	if (!new_node)
		return (NULL);
	parent->left = new_node;
	new_node->parent = parent;
	new_node->content = ft_strdup(content);
	new_node->left = NULL;
	new_node->right = NULL;
	(*element)--;
	ft_printf("---left---\n");
	return (new_node);
}

t_ASTNode	*add_right_node(t_ASTNode *parent, char *content, int *element)
{
	t_ASTNode	*new_node;

	new_node = malloc(sizeof(t_ASTNode));
	if (!new_node)
		return (NULL);
	parent->right = new_node;
	new_node->parent = parent;
	new_node->content = ft_strdup(content);
	new_node->left = NULL;
	new_node->right = NULL;
	(*element)--;
	ft_printf("---right---\n");
	return (new_node);
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

t_ASTNode	*add_node(t_input *input, t_ASTNode *current, int *element)
{
	t_ASTNode *new_node;

	if (!input->prev)
		new_node = add_left_node(current, input->content, element);
	else if (ft_strcmp(input->prev->content, "|") == 0)
		new_node = add_right_node(current, input->content, element);
	else if ((ft_strcmp(input->type, "here_doc") == 0) || (ft_strcmp(input->type, "less") == 0)
			|| (ft_strcmp(input->type, "great") == 0) || (ft_strcmp(input->type, "dgreat") == 0))
		new_node = add_right_node(current, input->content, element);
	else
		new_node = add_left_node(current, input->content, element);
	return (new_node);
}


t_ASTNode	*parse_to_ast(t_input *input)
{
	t_ASTNode	*head;
	t_ASTNode	*current;
	int			element;

	element = 1;
	while (input->next != NULL)
	{
		element++;
		input = input->next;
	}
	while ((input->prev != 0) && (ft_strcmp(input->type, "pipe") != 0))
		input = input->prev;
	head = create_ast(input->content, &element);
	current = head;
	input = input->next;
	while (element != 0)
	{
		while (input->next != NULL)
		{
			current = add_node(input, current, &element);
			input = input->next;
		}
		current = add_node(input, current, &element);
		while ((current->parent != 0) && (ft_strcmp(current->content, "|")) != 0)
			current = current->parent;
		while ((input->prev != 0) && (ft_strcmp(input->type, "pipe") != 0))
			input = destroy_node(input);
		if ((ft_strcmp(input->type, "pipe") == 0) || (!input->prev))
			input = destroy_node(input);
		if (element == 0)
			break ;
		while ((input->prev != 0) && (ft_strcmp(input->type, "pipe") != 0))
			input = input->prev;
	}
}

int	main(int argc, char *argv[])
{
	t_ASTNode	*head;
	t_input		*input;

	if (argc != 2)
		return (1);
	input = lexer(argv[1]);
	head = parse_to_ast(input);
}
