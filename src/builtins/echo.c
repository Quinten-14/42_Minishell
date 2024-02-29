#include "../../include/minishell.h"
#include "../../include/libft.h"

static int	number_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static bool	flag_checker(char *str)
{
    int	i;

    i = 1;
    while (str[i])
    {
        if (str[i] != 'n' && str[i] != '-')
            return (false);
        i++;
    }
    return (true);
}

static void	writer(char **strs, int position, bool flag)
{
	if (flag)
	{
		ft_putstr_fd(strs[position], 1);
		if (strs[position + 1] && strs[position][0] != '\0')
			write(1, " ", 1);
	}
	else
	{
		ft_putstr_fd(strs[position], 1);
		if (strs[position + 1] && strs[position][0] != '\0')
			write(1, " ", 1);
	}
}

int	echo_command(char **args)
{
    int		i;
    bool	n_flag;

    i = 1;
    n_flag = false;
    if (number_args(args) > 1)
    {
        if (args[i][0] == '-' && flag_checker(args[i]))
        {
            n_flag = true;
            i++;
        }
        while (args[i])
        {
            writer(args, i, true);
            i++;
        }
    }
    if (n_flag == false)
        write(1, "\n", 1);
    return (SUCCESS);
}
