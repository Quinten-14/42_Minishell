#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "./data.h"

/* Input */
void		input(t_data *data);
char		**convert_input(char *s);
t_input		*lexer(char *prompt);
t_ASTNode	*add_ast_node(t_input *input, t_ASTNode *current, int *element);
t_input		*destroy_node(t_input *input);
t_ASTNode	*parse_to_ast(t_input *input);
t_ASTNode	*delete_ast_node(t_ASTNode *current);
void		free_ast(t_ASTNode *head);

/* Environment */
t_env		*init_env_list(char **envp);
char		*get_from_env(t_env *env, char *search);
void		update_env(t_env **head, char *var, char *update_val);
void		create_env(t_env **env, char *var, char *update_val);
void		delete_env(t_env **env, char *search);

/* Expander */
void		expander(t_ASTNode *head, t_env *env);

/* Builtins */
int			env_command(t_env *env);
int			get_pwd(void);
void		unset_command(t_env *env, char **strs);
void		cd_command(char **strs, t_env *env);
void		exit_command(t_data *data, char **prompt);
int			echo_command(char **args);
void		export_command(char **strs, t_env *env);

/* Utils */
void		throw_fatal(char *str, int exit_code);
void		free_array(char **array);

#endif
