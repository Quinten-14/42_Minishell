#include "../../include/minishell.h"

/* This file has the error thrower in it */

// PRE-ALPHA VERSION

int throw_error(char *str, int exit_code)
{
    printf("%s\n", str);
    return (exit_code);
}
