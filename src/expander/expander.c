#include "../../include/libft.h"
#include "../../include/minishell.h"

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
        if (node->content[*i] == '$' || node->content[*i] == '\"' || node->content[*i] == '\'')
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

char	*join_and_free_old(char *result, char *str_to_join)
{
	char	*new_result;

	new_result = ft_strjoin(result, str_to_join);
	free(result);
	return (new_result);
}

char	*handle_dollar(char *result, t_ASTNode *node, t_env *env, int *i)
{
	if (node->content[*i + 1] == '$')
	{
		result = join_and_free_old(result, getProcessID());
		(*i)++;
	}
	else if (node->content[*i + 1] == '?')
	{
		result = join_and_free_old(result, "12");
		(*i)++;
	}
	else
		result = join_and_free_old(result, var_expansion(node, env, i));
	return (result);
}

void	expander_checker(t_ASTNode *node, t_env *env)
{
    int		i;
    char	*result;
    char	temp[2];

    result = ft_strdup("");
    i = 0;
    while (node->content[i])
    {
        if (node->content[i] == '$')
            result = handle_dollar(result, node, env, &i);
        else if (node->content[i] != '\"')
        {
            temp[0] = node->content[i];
            temp[1] = '\0';
            result = join_and_free_old(result, temp);
        }
        i++;
    }
    node->content = ft_strdup(result);
    free(result);
}

void	expander(t_ASTNode *head, t_env *env)
{
	if (!head)
		return ;
	if (ft_strcmp(head->type, "Var-Expansion") == 0)
	{
		expander_checker(head, env);
		if (DEBUG_MODE)
			printf("After Expander: %s\n", head->content);
	}
	expander(head->right, env);
	expander(head->left, env);
}
