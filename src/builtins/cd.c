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
