#include "../../../include/minishell.h"
#include "../../../include/libft.h"

int	check_type(char *str)
{
	if (ft_strcmp(str, "here_doc") == 0 || ft_strcmp(str, "less") == 0)
		return (1);
	else if (ft_strcmp(str, "great") == 0 || ft_strcmp(str, "dgreat") == 0)
		return (1);
	else if (ft_strcmp(str, "pipe") == 0)
		return (1);
	return (0);
}

t_input	*check_syntax(t_input *input_list)
{
	t_input	*current;

	current = input_list;
	while (current && current->next)
	{
		if (check_type(current->type) && check_type(current->next->type))
		{
			free_input(input_list);
			return (NULL);
		}
		current = current->next;
	}
	return (input_list);
}
