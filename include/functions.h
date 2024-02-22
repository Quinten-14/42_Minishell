#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include "./data.h"

void    input(t_data *data);
char    **split_input(char const *s);
t_input *lexer(char *prompt);
t_env   *init_env_list(char **envp);

#endif
