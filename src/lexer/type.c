#include "../../include/minishell.h"
#include "../../include/libft.h"

static bool  check_redir(char *str)
{
    if (ft_strcmp(str, "<<") == 0 || ft_strcmp(str, "<") == 0 ||
            ft_strcmp(str, ">>") == 0 || ft_strcmp(str, ">") == 0)
        return (true);
    else
        return (false);
}

static char *redir_type(char *str)
{
    if (ft_strcmp(str, "<<") == 0)
        return ("here_doc");
    else if (ft_strcmp(str, "<") == 0)
        return ("less");
    else if (ft_strcmp(str, ">") == 0)
        return ("great");
    else
        return ("dgreat");
}

static char *var_type(char *str)
{
    int amount_signs;
    int i;

    amount_signs = 0;
    i = 0;
    while(str[i])
    {
        if (str[i] == '$')
            amount_signs++;
        i++;
    }
    if (amount_signs % 2 == 0)
        return ("Process-ID");
    else
        return ("Var-Expension");
}

char    *check_types(char *str, int i, char **arr)
{
    char    *type;
    static bool command_inline;

    if (i == 0)
        command_inline = false;
    if (check_redir(str) == true)
        type = redir_type(str);
    else if (ft_strcmp(str, "|") == 0)
    {
        type = "pipe";
        command_inline = false;
    }
    else if (i > 0 && (check_redir(arr[i - 1]) == true))
        type = "file";
    else if (ft_strchr(str, '$') != 0)
        type = var_type(str);
    else if (i == 0 || !command_inline)
    {
        type = "command";
        command_inline = true;
    }
    else
        type = "word";
    return (type);
}

// normally works fine except for 
// grep "error" log.txt | sort > sorted_errors.txt
