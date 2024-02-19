#include "../include/minishell.h"
#include <readline/readline.h>

static void setup_shell(char **envp, t_data *data)
{
    data->env = envp;
    data->env_list = *init_env_list(envp);
}

int main(int ac, char **av, char **envp)
{
    t_input *input;
    t_data  data;
    char    **splitted;

    (void)ac;
    (void)av;
    setup_shell(envp, &data);
    using_history();
    while (1)
    {
        data.prompt = readline("Minishell-42: ");
        add_history(data.prompt);
        input = lexer(data.prompt);
        splitted = ft_split(data.prompt, ' '); //this is just for testing;
        if (ft_strcmp(splitted[0], "env") == 0)
            put_env(&data.env_list);
        if (ft_strcmp(splitted[0], "cd") == 0)
            cd_command(splitted, &data.env_list);
        if (ft_strcmp(splitted[0], "pwd") == 0)
            get_pwd();
        (void)input;
        //parser(input);
    }
}
