#include "../../include/minishell.h"
#include "../../include/ft_printf.h"

/* This file has the error thrower in it */

// PRE-ALPHA VERSION

int throw_error(char *str, int exit_code)
{
    ft_printf("%s\n", str);
    return (exit_code);
}
