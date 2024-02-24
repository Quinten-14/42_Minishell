#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include "./data.h"

/* Input */
void    input(t_data *data);
char    **split_input(char const *s);
t_input *lexer(char *prompt);

/* Environment */
t_env *init_env_list(char **envp);
char    *get_from_env(t_env *env, char *search);
void	update_env(t_env **head, char *var, char *update_val);
void    create_env(t_env **env, char *var, char *update_val);
void    delete_env(t_env **env, char *search);

/* Builtins */
int env_command(t_env *env);
int get_pwd(void);
void    unset_command(t_env *env, char **strs);
void    cd_command(char **strs, t_env *env);
void    exit_command(t_data *data, char **prompt);

/* Utils */
void    throw_fatal(char *str, int exit_code);

#endif
