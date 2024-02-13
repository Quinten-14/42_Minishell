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

char    *check_types(char *str, int i, char **arr)
{
    char    *type;
    static bool command_inline;

    if (i == 0)
        command_inline = false;
    if (check_redir(str) == true)
        type = "redirection";
    else if (ft_strcmp(str, "|") == 0)
    {
        type = "pipe";
        command_inline = false;
    }
    else if (i == 0 || ((i > 1 && check_redir(arr[i-2]) == true) && !command_inline))
    {
        type = "command";
        command_inline = true;
    }
    else
        type = "word";
    return (type);
}
