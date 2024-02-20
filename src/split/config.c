/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-paep <lde-paep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:26:22 by lde-paep          #+#    #+#             */
/*   Updated: 2024/02/20 12:20:11 by lde-paep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/minishell.h"

char	**split_input(char const *s);
void	handle_special(char *str, char *new_str, int *i, int *j);
int		handle_single_quote(char *str, char *new_str, int *i, int *j);
int		handle_double_quote(char *str, char *new_str, int *i, int *j);

int	count_size(char	*str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strchr("<>|;&$", str[i]))
			len += 2;
		if (str[i] == 34 || str[i] == 39)
			len++;
		i++;
	}
	return (len + i + 1);
}

int	adjust_str(char *str, char *new_str, int size)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < size - 1 && str[j])
	{
		if (str[j] == 34)
		{
			if (!handle_double_quote(str, new_str, &i, &j))
				return (0);
		}
		else if (str[j] == 39)
		{
			if (!handle_single_quote(str, new_str, &i, &j))
				return (0);
		}
		else if (ft_strchr("|<>;&", str[j]))
			handle_special(str, new_str, &i, &j);
		else
			new_str[i++] = str[j++];
	}
	return (1);
}

char	**convert_input(char *str)
{
	int		size;
	char	*new_str;
	char	**split;

	size = count_size(str);
	new_str = ft_calloc(sizeof(char), size);
	if (!new_str)
		return (0);
	if (!adjust_str(str, new_str, size))
	{
		free(new_str);
		return (0);
	}
	split = split_input(new_str);
	free(new_str);
	if (!split)
		return (0);
	return (split);
}

/*
int	main(int argc, char *argv[])
{
	char	**split;
	int		i;

	if (argc != 2)
		return (0);
	split = convert_input(argv[1]);
	if (!split)
	{
		ft_printf("Syntax error\n");
		return (0);
	}
	i = 0;
	while (split[i])
	{
		ft_printf("%s\n", split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}
*/
