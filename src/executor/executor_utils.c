#include "../../include/libft.h"
#include "../../include/minishell.h"

int	amount_args(t_ASTNode *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->left;
	}
	return (i);
}

char	**arg_arr(t_ASTNode *node)
{
	char		**arr;
	int			i;
	t_ASTNode	*temp_node;

	arr = malloc(sizeof(char *) * (amount_args(node) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	temp_node = node;
	while (temp_node)
	{
		arr[i] = temp_node->content;
		i++;
		temp_node = temp_node->left;
	}
	arr[i] = NULL;
	return (arr);
}
