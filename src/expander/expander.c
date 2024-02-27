#include "../../include/minishell.h"

// this file goes over the AST tree and finds nodes with the type Var-Expension
// then it will get the var from the env var list.

// Function to replace the node content if var is found
// if not just empty it

void    fillin_var(t_ASTNode *node, t_env *env)
{
    if (get_from_env(env, node->content) != NULL)
        node->content = get_from_env(env, node->content);
    else
        node->content = "";
}
