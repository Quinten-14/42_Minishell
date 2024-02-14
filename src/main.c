#include "../include/minishell.h"
#include <readline/readline.h>

int main(void)
{
    char    *str;
    t_input *input;

    using_history();
    while (1)
    {
        str = readline("Minishell-42: ");
        add_history(str);
        input = lexer(str);
        (void)input;
        //parser(input);
    }
}
