#include "../../include/minishell.h"
#include "../../include/libft.h"

char    *get_type(char *str)
{
    if (ft_strcmp(str, "|") == 0)
        return ("pipe");
    else if (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0 || 
            ft_strcmp(str, ">>") == 0)
        return ("redirect");
    else if (ft_strcmp(str, "<<") == 0)
        return ("doc");
    else
        return ("word");
}
