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
        printf("%s\n", str);
    }
}
