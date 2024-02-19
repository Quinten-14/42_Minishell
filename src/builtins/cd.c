#include "../../include/minishell.h"

/* CD Basics */

/*
 * When Doing CD it should bring you back to the home path
 * When Doing CD - it should bring you to the OLDPWD
 * You can use both relative and absolute paths
 * We need to update OLDPWD and PWD environment variables
 * If minishell started and no OLDPWD set it should give a error message -
 * when doing CD -
*/

void    cd_command(t_input *input, t_env *env)
{
    char    *old_pwd;
    char    CWD[PATH_MAX];
    (void)input;
    old_pwd = getcwd(CWD, PATH_MAX);
    if (!old_pwd)
        return ;
    old_pwd = ft_strjoin("OLDPWD=", old_pwd);
    add_node(&env, ft_strjoin("OLDPWD=", old_pwd));
}
