#include "../../include/minishell.h"
#include "../../include/libft.h"

// the lexer gives info like the type of the word after split
// the options can be:
// Command, word, pipe, redirect

static int arr_len(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
}

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

// split the prompt and then tokenize the strings to types
// The data is stored in a linked list from the left to the right.
char    ***lexer(char *prompt)
{
    return (NULL);
}

/*
char    ***lexer(char *prompt)
{
    char    **splitted;
    char    ***result;
    int i;

    i = 0;
    splitted = ft_split(prompt, ' ');
    result = (char ***)malloc(sizeof(char **) * (arr_len(splitted) + 1));
    if (!result)
        return (NULL);
    while (splitted[i])
    {
        result[i] = (char **)malloc(sizeof(char *) * (2));
        if (!result[i])
            return (NULL);
        result[i][0] = splitted[i];
        if (i == 0 || (ft_strcmp(splitted[i-1], "|") == 0))
            result[i][1] = "command";
        else
            result[i][1] = get_type(splitted[i]);
        i++;
    }
    result[i] = NULL;
    print_arr(result);
    return (result);
}
*/
