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
    struct s_input_list *prev;
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

/* Enviroment Struct */
typedef struct  s_env
{
    char    *content;
    char    *var_name;
    struct s_env    *next;
}           t_env;

typedef struct  s_data
{
    char    **env;
    t_env   env_list;
}           t_data;

/* Functions */

int get_pwd(void);
int ft_echo(char **args);
t_input     *lexer(char *prompt);
char    *check_types(char *str, int i, char **arr);
int quotes_checker(char *str);
int throw_error(char *str, int exit_code);
t_env   *init_env_list(char **envp);
int put_env(t_env *env);
int node_exists(char *str, t_env **head);

#endif
