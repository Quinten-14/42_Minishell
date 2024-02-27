#include "../../include/minishell.h"

int array_len(void **array)
{
    int i;

    i = 0;
    while (array[i])
        i++;
    return (i);
}

void    free_array(void **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        array[i] = NULL;
        i++;
    }
    free(array);
    array = NULL;
}
