#include "../include/minishell.h"
#include <readline/readline.h>

int main(void)
{
    char    *str;
    char    **seperated;

    using_history();
    while (1)
    {
        str = readline("Minishell-42: ");
        add_history(str);
        seperated = ft_split(str, ' ');
        if (ft_strcmp(seperated[0], "pwd") == 0)
            get_pwd();
        else if (ft_strcmp(seperated[0], "echo") == 0)
            ft_echo(seperated);
        else
            printf("Command Not Found\n");
    }
}

// this is just test code
// Bug: If you do tpwd it just prints it but pwdt activates the pwd builtin
// (Normally fixed by using strcmp instead of strncmp

// We shouldnt forget to put everything in lowercase to make it easier to get
// the commands working properly (this doesnt work for everything to so we need
// a way to check if we have an argument of option. Maybe we can check - Flags
