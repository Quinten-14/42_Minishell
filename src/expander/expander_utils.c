#include "../../include/minishell.h"
#include "../../include/libft.h"

// function to check the type of expansion. Also make it fill in the right
// stuff so for example
// echo $hello$hello gives worldworld if hello=world
// echo $$hello gives [PID]hello

char	*join_char(char *result, char char_to_join)
{
	char	*new_result;
	char	temp[2];

	temp[0] = char_to_join;
	temp[1] = '\0';
	new_result = ft_strjoin(result, temp);
	free(result);
	return (new_result);
}

char	*double_quote(char *result, t_ASTNode *node, t_data *data, int *i)
{
	while (node->content[++(*i)] != '\"')
	{
		if (node->content[*i] == '$')
			result = handle_dollar(result, node, data, i);
		else
			result = join_char(result, node->content[*i]);
	}
	return (result);
}
