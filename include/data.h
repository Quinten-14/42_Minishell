#ifndef DATA_H
# define DATA_H

/* Enum Section */

typedef enum e_ret_status
{
	ERROR,
	SUCCESS,
}				t_ret_status;

/* Struct Section */

typedef struct s_input_list
{
	char				*content;
	char				*type;
	struct s_input_list	*next;
	struct s_input_list	*prev;
}				t_input;

typedef struct s_ASTNode
{
	struct s_ASTNode	*left;
	struct s_ASTNode	*right;
	struct s_ASTNode	*parent;
	char				*content;
	char				*type;
}				t_ASTNode;

typedef struct s_env
{
	char			*content;
	char			*var_name;
	bool			exported;
	struct s_env	*next;
}				t_env;

typedef struct s_data
{
	char	**env;
	t_env	env_list;
	char	*prompt;
	bool	exit;
	int		ret;
}				t_data;

typedef struct s_signal
{
	bool	ctrl_c;
	bool	ctrl_d;
}				t_signal;

#endif
