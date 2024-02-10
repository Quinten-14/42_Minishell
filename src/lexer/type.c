#include "../../include/minishell.h"
#include "../../include/libft.h"

static char *redirect_type(char *str)
{
    if (ft_strcmp(str, "<") == 0)
        return ("less");
    else if (ft_strcmp(str, "<<") == 0)
        return ("here_doc");
    else if (ft_strcmp(str, ">") == 0)
        return ("great");
    else
        return ("dgreat");
}

static char *expansion_types(char *str)
{
    int nbr_dollar;
    int i;

    i = 0;
    nbr_dollar = 0;
    while (str[i])
    {
        if (str[i] == '$')
            nbr_dollar++;
        i++;
    }
    if (nbr_dollar % 2 == 0)
        return ("processID");
    else
        return ("expansion");

}

static bool expansion_checker(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return (true);
        i++;
    }
    return (false);
}

char    *get_type(char *str)
{
    if (ft_strcmp(str, "|") == 0)
        return ("pipe");
    else if (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0 || 
            ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0)
        return (redirect_type(str));
    else if (expansion_checker(str) == true)
        return (expansion_types(str));
    else
        return ("word");
}
