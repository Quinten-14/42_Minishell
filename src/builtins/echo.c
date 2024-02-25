#include "../../include/minishell.h"
#include "../../include/libft.h"

static int    number_args(char **args)
{
    int i;

    i = 0;
    while(args[i])
        i++;
    return (i);
}

static bool flag_checker(char *str)
{
    int i;

    i = 1;
    while (str[i])
    {
        if (str[i] != 'n')
            return (false);
        i++;
    }
    return (true);
}

int echo_command(char **args)
{
    int i;
    bool    n_flag;

    i = 1;
    n_flag = false;
    if (number_args(args) > 1)
    {
        while (args[i])
        {
            if (args[i][0] == '-')
                if (flag_checker(args[i]) == true)
                    n_flag = true;
                else
                {
                    ft_putstr_fd(args[i], 1);
                    write(1, " ", 1);
                }
            else
            {
                ft_putstr_fd(args[i], 1);
                if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
            }
            i++;
        }
    }
    if (n_flag == false)
        write(1, "\n", 1);
    return (SUCCESS);
}
