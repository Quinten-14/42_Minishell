#include "../../../include/libft.h"
#include "../../../include/minishell.h"

void	handle_special(char *str, char *new_str, int *i, int *j)
{
	new_str[*i] = ' ';
	new_str[++(*i)] = str[*j];
	if (str[*j] == str[(*j) + 1])
		new_str[++(*i)] = str[++(*j)];
	new_str[++(*i)] = ' ';
	(*i)++;
	(*j)++;
}

int	handle_single_quote(char *str, char *new_str, int *i, int *j)
{
//	new_str[(*i)++] = ' ';
	new_str[(*i)++] = str[(*j)++];
	while (str[*j] != 39)
	{
		if (!str[*j])
			return (0);
		new_str[(*i)++] = str[(*j)++];
	}
	new_str[(*i)++] = str[(*j)++];
//	new_str[(*i)++] = ' ';
	return (1);
}

int	handle_double_quote(char *str, char *new_str, int *i, int *j)
{
//	new_str[(*i)++] = ' ';
	new_str[(*i)++] = str[(*j)++];
	while (str[*j] != 34)
	{
		if (!str[*j])
			return (0);
		new_str[(*i)++] = str[(*j)++];
	}
	new_str[(*i)++] = str[(*j)++];
//	new_str[(*i)++] = ' ';
	return (1);
}

bool	check_expansion(char *str)
{
	int	i;

	if (ft_strchr(str, '$') == 0)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		else if (str[i] == 34)
		{
			while (str[++i] != 34)
			{
				if (str[i] == '$')
					return (true);
			}
		}
		else if (str[i] == 39)
		{
			while (str[++i] != 39)
				;
		}
		i++;
	}
	return (false);
}
