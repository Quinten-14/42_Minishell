#include "../../include/minishell.h"
#include "../../include/libft.h"
#include <stdio.h>

// echo prints the input back out. If you do echo "Testing"
// it prints Testing to the terminal.
// If you put -n behind it then it doesn't print the newline at the end

// function to see the amount of arguments. <= 1 is not possible.
// Check if the second argument is -n. If not just print the input
// If -n is found print without newline. Text should be infront of new prompt

static int    number_args(char **args)
{
    int i;

    i = 0;
    while(args[i])
        i++;
    return (i);
}

int ft_echo(char **args)
{
    int i;
    int amount_args;
    bool n_flag;

    amount_args = number_args(args) - 1;
    i = 1;
    n_flag = false;
    if (ft_strcmp(args[1], "-n") == 0)
    {
        n_flag = true;
        i++;
    }
    while (i < amount_args)
    {
        printf("%s ", args[i]);
        i++;
    }
    if (i == amount_args && n_flag == false)
        printf("%s\n", args[i]);
    else if (i == amount_args && n_flag == true)
        printf("%s", args[i]);
    return (0);
}

// has as argument an array of strings

// Still need to find a way to work with the spaces (Done normally)
