#include "../include/minishell.h"
#include <readline/readline.h>

int main(void)
{
    char    *str;

    using_history();
    while (1)
    {
        str = readline("Minishell-42: ");
        add_history(str);
        lexer(str);
    }
}

// this is just test code
// Bug: If you do tpwd it just prints it but pwdt activates the pwd builtin
// (Normally fixed by using strcmp instead of strncmp

// We shouldnt forget to put everything in lowercase to make it easier to get
// the commands working properly (this doesnt work for everything to so we need
// a way to check if we have an argument of option. Maybe we can check - Flags
