#include "../../../include/minishell.h"
#include "../../../include/libft.h"


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
	if (DEBUG_MODE)
		printf("---left---\n");
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
	if (DEBUG_MODE)
		printf("---right---\n");
	return (new_node);
}

t_ASTNode	*add_ast_node(t_input *input, t_ASTNode *current, int *element)
{
	t_ASTNode	*new_node;

	if (!input->prev)
		new_node = add_left_node(current, input->content, element);
	else if (ft_strcmp(input->prev->content, "|") == 0)
		new_node = add_right_node(current, input->content, element);
	else if ((ft_strcmp(input->type, "great") == 0)
		|| (ft_strcmp(input->type, "dgreat") == 0))
		new_node = add_right_node(current, input->content, element);
	else if ((ft_strcmp(input->type, "here_doc") == 0)
		|| (ft_strcmp(input->type, "less") == 0))
		new_node = add_right_node(current, input->content, element);
	else
		new_node = add_left_node(current, input->content, element);
	if (DEBUG_MODE)
		printf("%s \n", input->content);
	return (new_node);
}
