#include "../../include/libft.h"
#include "../../include/minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->env = envp;
	data->prompt = NULL;
	data->exit = false;
	data->ret = 0;
}

t_ASTNode	*input(t_data *data)
{
	t_input		*input;
	t_ASTNode	*head;

	data->prompt = readline("Minishell-42: ");
	if (data->prompt == NULL)
		return (handle_d(data));
	if (ft_strlen(data->prompt) == 0)
	{
		return (NULL);
	}
	input = lexer(data->prompt);
	if (!input)
		return (ft_error("bash: syntax error"));
	add_history(data->prompt);
    // use the input for the parser to then make a AST
	head = parse_to_ast(input);
	if (!head)
		return (ft_error("bash: syntax error"));
	expander(head, data);
		return (NULL);
	return (head);
}
