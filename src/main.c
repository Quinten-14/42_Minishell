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
        if (ft_strncmp(str, "pwd", 3) == 0)
            get_pwd();
        else
            printf("%s\n", str);
    }
}

// this is just test code
