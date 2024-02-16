#include "../include/minishell.h"
#include <readline/readline.h>

static void setup_shell(char **envp, t_data *data)
{
    data->env = envp;
    data->env_list = *init_env_list(envp);
}

int main(int ac, char **av, char **envp)
{
    char    *str;
    t_input *input;
    t_data  data;

    (void)ac;
    (void)av;
    setup_shell(envp, &data);
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
