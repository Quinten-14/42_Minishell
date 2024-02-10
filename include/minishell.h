#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
//#include <sys/syslimits.h>
#include <unistd.h>
#include "libft.h"
#include <stdbool.h>
#include <limits.h>

/* Linked Lists */
typedef struct  s_input_list
{
    char    *content;
    char    *type;
    struct s_input_list *next;
}           t_input;

int get_pwd(void);
int ft_echo(char **args);
char    *get_type(char *str);
char    ***lexer(char *prompt);

#endif
