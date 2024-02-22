#include "../../include/libft.h"
#include "../../include/minishell.h"

void	line_reader(t_data *data)
{
	data->prompt = readline("Minishell-42: ");
	if (ft_strlen(data->prompt) == 0)
		return ;
	add_history(data->prompt);
}

void	input(t_data *data)
{
	t_input	*input;

	line_reader(data);
	input = lexer(data->prompt);
    if (!input)
        return ;
    // use the input for the parser to then make a AST
}
