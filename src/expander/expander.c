#include "../../include/libft.h"
#include "../../include/minishell.h"

char	*join_char(char *result, char char_to_join);
char	*double_quote(char *result, t_ASTNode *node, t_data *data, int *i);

// this file goes over the AST tree and finds nodes with the type Var-Expension
// then it will get the var from the env var list.

// Function to replace the node content if var is found
// if not just empty it

char	*var_expansion(t_ASTNode *node, t_env *env, int *i)
{
	char	*result;
	char	*temp;
	char	*new_result;

	result = ft_strdup("");
	(*i)++;
	while (node->content[*i] && node->content[*i] != '$'
		&& node->content[*i] != '=')
	{
		if (node->content[*i] == '$'
			|| node->content[*i] == '\"' || node->content[*i] == '\'')
			break ;
		temp = ft_substr(node->content, *i, 1);
		new_result = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = new_result;
		(*i)++;
	}
	(*i)--;
	result = get_from_env(env, result);
	if (!result)
		result = ft_strdup("");
	return (result);
}

char	*join_free_old(char *result, char *str_to_join)
{
	char	*new_result;

	new_result = ft_strjoin(result, str_to_join);
	free(result);
	return (new_result);
}

char	*handle_dollar(char *result, t_ASTNode *node, t_data *data, int *i)
{
	if (node->content[*i + 1] == '$')
	{
		result = join_free_old(result, get_process_id());
		(*i)++;
	}
	else if (node->content[*i + 1] == '?')
	{
		result = join_free_old(result, ft_itoa(data->ret));
		(*i)++;
	}
	else if (!node->content[*i + 1])
		result = join_free_old(result, "$");
	else
		result = join_free_old(result, var_expansion(node, data->env_list, i));
	return (result);
}

void	expander_checker(t_ASTNode *node, t_data *data)
{
	int		i;
	char	*result;

	result = ft_strdup("");
	i = 0;
	while (node->content[i])
	{
		if (node->content[i] == '\'')
		{
			while (node->content[++i] != '\'')
				result = join_char(result, node->content[i]);
		}
		else if (node->content[i] == '\"')
			result = double_quote(result, node, data, &i);
		else if (node->content[i] == '$')
			result = handle_dollar(result, node, data, &i);
		else
			result = join_char(result, node->content[i]);
		i++;
	}
	node->content = ft_strdup(result);
	free(result);
}

void	expander(t_ASTNode *head, t_data *data)
{
	if (!head)
		return ;
	/*
	if (ft_strcmp(head->type, "Var-Expansion") == 0)
	{
		expander_checker(head, data);
		if (DEBUG_MODE)
			printf("After Expander: %s\n", head->content);
	}
	*/
	expander_checker(head, data);
	if (DEBUG_MODE)
		printf("After Expander: %s\n", head->content);
	expander(head->right, data);
	expander(head->left, data);
}
