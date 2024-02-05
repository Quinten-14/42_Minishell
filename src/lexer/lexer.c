#include "../../include/minishell.h"
#include "../../include/libft.h"

// the lexer gives info like the type of the word after split
// the options can be:
// Command, word, pipe, redirect

static void print_arr(char ***matrix)
{
    int i;

    i = 0;
    if (matrix != NULL) {
        while (matrix[i] != NULL)
        {
            if (matrix[i][0] != NULL && matrix[i][1] != NULL) {
                printf("%s %s\n", matrix[i][0], matrix[i][1]);
            }
            i++;
        }
    }
}

char    ***lexer(char *prompt)
{
    char    **splitted;
    char    ***result;
    int i;

    i = 0;
    splitted = ft_split(prompt, ' ');
    result = (char ***)malloc(sizeof(char **) * (1));
    if (!result)
        return (NULL);
    while (splitted[i])
    {
        result[i][0] = splitted[i];
        result[i][1] = "word";
        i++;
    }
    result[i] = NULL;
    print_arr(result);
    return (result);
}
