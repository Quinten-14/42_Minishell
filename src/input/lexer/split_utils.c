#include "../../../include/libft.h"

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
	new_str[(*i)++] = ' ';
	new_str[(*i)++] = str[(*j)++];
	while (str[*j] != 39)
	{
		if (!str[*j])
			return (0);
		new_str[(*i)++] = str[(*j)++];
	}
	new_str[(*i)++] = str[(*j)++];
	new_str[(*i)++] = ' ';
	return (1);
}

int	handle_double_quote(char *str, char *new_str, int *i, int *j)
{
	new_str[(*i)++] = ' ';
	new_str[(*i)++] = str[(*j)++];
	while (str[*j] != 34)
	{
		if (!str[*j])
			return (0);
		new_str[(*i)++] = str[(*j)++];
	}
	new_str[(*i)++] = str[(*j)++];
	new_str[(*i)++] = ' ';
	return (1);
}
