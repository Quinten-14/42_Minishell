#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
//#include <sys/syslimits.h>
#include <unistd.h>
#include "libft.h"
#include <stdbool.h>
#include <limits.h>

/* Defines */

#ifndef DEBUG_MODE
# define DEBUG_MODE true
#endif

/* Enums */

typedef enum    e_exit
{
    SUCCESS,
    ERROR,
}               t_exit;

/* Linked Lists */
typedef struct  s_input_list
{
    char    *content;
    char    *type;
    struct s_input_list *next;
}           t_input;

/* Abstract Syntax Tree */
typedef struct  s_ASTNode
{
    char    *type;
    union
    {
        char    *group;
        struct
        {
            struct s_ASTNode    *left;
            struct s_ASTNode    *right;
            char    *content;
        } u_expression;
    };
}           t_ASTNode;

/* Functions */

int get_pwd(void);
int ft_echo(char **args);
t_input     *lexer(char *prompt);
char    *check_types(char *str, int i, char **arr);
int quotes_checker(char *str);

#endif
