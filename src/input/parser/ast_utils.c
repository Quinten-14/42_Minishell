#include "../../../include/minishell.h"
#include "../../../include/libft.h"

t_ASTNode	*delete_ast_node(t_ASTNode *current)
{
	t_ASTNode	*parent;

	if (!current)
		return (NULL);
	parent = current->parent;
	if (parent)
	{
		if (parent->left == current)
			parent->left = NULL;
		if (parent->right == current)
			parent->right = NULL;
	}
	free(current->content);
	free(current->type);
	free(current);
	return (parent);
}

t_ASTNode	*add_left_node(t_ASTNode *parent, t_input *input, int *element)
{
	t_ASTNode	*new_node;

	new_node = malloc(sizeof(t_ASTNode));
	if (!new_node)
		return (NULL);
	parent->left = new_node;
	new_node->parent = parent;
	new_node->content = ft_strdup(input->content);
	new_node->type = ft_strdup(input->type);
	new_node->left = NULL;
	new_node->right = NULL;
	(*element)--;
	if (DEBUG_MODE)
		printf("---left---\n");
	return (new_node);
}

t_ASTNode	*add_right_node(t_ASTNode *parent, t_input *input, int *element)
{
	t_ASTNode	*new_node;

	new_node = malloc(sizeof(t_ASTNode));
	if (!new_node)
		return (NULL);
	parent->right = new_node;
	new_node->parent = parent;
	new_node->content = ft_strdup(input->content);
	new_node->type = ft_strdup(input->type);
	new_node->left = NULL;
	new_node->right = NULL;
	(*element)--;
	if (DEBUG_MODE)
		printf("---right---\n");
	return (new_node);
}

t_ASTNode	*add_ast_node(t_input *input, t_ASTNode *current, int *element)
{
	t_ASTNode	*new_node;

	if (!input->prev)
		new_node = add_left_node(current, input, element);
	else if (ft_strcmp(input->prev->content, "|") == 0)
		new_node = add_right_node(current, input, element);
	else if ((ft_strcmp(input->type, "great") == 0)
		|| (ft_strcmp(input->type, "dgreat") == 0))
		new_node = add_right_node(current, input, element);
	else if ((ft_strcmp(input->type, "here_doc") == 0)
		|| (ft_strcmp(input->type, "less") == 0))
		new_node = add_right_node(current, input, element);
	else
		new_node = add_left_node(current, input, element);
	if (DEBUG_MODE)
		printf("content = %s, type = %s\n", new_node->content, new_node->type);
	return (new_node);
}
