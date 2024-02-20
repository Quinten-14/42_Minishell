#include "../../include/libft.h"
#include "../../include/minishell.h"

static bool	check_redir(char *str)
{
	if (ft_strcmp(str, "<<") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str,
			">>") == 0 || ft_strcmp(str, ">") == 0)
		return (true);
	else
		return (false);
}

static bool	check_pipe(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "||") == 0
		|| ft_strcmp(str, "&&") == 0)
		return (true);
	else
		return (false);
}

static char	*redir_type(char *str, bool *command_inline)
{
	if (ft_strcmp(str, "<<") == 0)
		return ("here_doc");
	else if (ft_strcmp(str, "<") == 0)
		return ("less");
	else if (ft_strcmp(str, ">") == 0)
		return ("great");
	else if (ft_strcmp(str, ">>") == 0)
		return ("dgreat");
	else if (ft_strcmp(str, "|") == 0)
	{
		*command_inline = false;
		return ("pipe");
	}
	else if (ft_strcmp(str, "||") == 0)
		return ("or");
	else
		return ("and");
}

static char	*var_type(char *str)
{
	int	amount_signs;
	int	i;

	amount_signs = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			amount_signs++;
		i++;
	}
	if (amount_signs % 2 == 0)
		return ("Process-ID");
	else if (amount_signs % 2 == 1 && ft_strcmp(str, "$?") == 0)
		return ("Last-Exit");
	else
		return ("Var-Expension");
}

char	*check_types(char *str, int i, char **arr)
{
	char		*type;
	static bool	command_inline;

	if (i == 0)
		command_inline = false;
	if (check_redir(str) == true || check_pipe(str) == true)
		type = redir_type(str, &command_inline);
	else if (i > 0 && (check_redir(arr[i - 1]) == true))
		type = "file";
	else if (ft_strchr(str, '$') != 0)
		type = var_type(str);
	else if (i == 0 || !command_inline)
	{
		type = "command";
		command_inline = true;
	}
	else
		type = "word";
	return (type);
}

// normally works fine except for
// grep "error" log.txt | sort > sorted_errors.txt
