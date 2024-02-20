#include "../include/minishell.h"
#include <readline/readline.h>

#include "../include/ft_printf.h"

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
		if (!ft_strlen(str))
			continue;
        add_history(str);
        input = lexer(str);
        if (ft_strcmp(str, "env") == 0)
            put_env(&data.env_list);
        (void)input;
        //parser(input);
    }
}
