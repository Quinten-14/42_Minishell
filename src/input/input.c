#include "../../include/libft.h"
#include "../../include/minishell.h"

void	input(t_data *data)
{
	t_input		*input;
	char		**splitted;    // just for testing
	t_ASTNode	*head;

	data->prompt = readline("Minishell-42: ");
	if (ft_strlen(data->prompt) == 0)
	{
		return ;
	}
	input = lexer(data->prompt);
	if (!input)
		return ;
	add_history(data->prompt);
    // use the input for the parser to then make a AST
	head = parse_to_ast(input);
	if (!head)
		return ;
	expander(head, &data->env_list);
	splitted = ft_split(data->prompt, ' ');
	if (ft_strcmp(splitted[0], "pwd") == 0)
		get_pwd();
	if (ft_strcmp(splitted[0], "env") == 0)
	{
		if (env_command(&data->env_list) == -1)
			return ;
	}
	if (ft_strcmp(splitted[0], "unset") == 0)
		unset_command(&data->env_list, splitted);
	if (ft_strcmp(splitted[0], "cd") == 0)
		cd_command(splitted, &data->env_list);
	if (ft_strcmp(splitted[0], "exit") == 0)
		exit_command(data, splitted);
	if (ft_strcmp(splitted[0], "echo") == 0)
		echo_command(splitted);
	if (ft_strcmp(splitted[0], "export") == 0)
		export_command(splitted, &data->env_list);
	free_array(splitted);
	free_ast(head);
}
