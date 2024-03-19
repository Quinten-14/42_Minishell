#include "../../include/minishell.h"
#include "../../include/libft.h"

void	increment_shell_lvl(t_env *env)
{
	int	curr_lvl;
	char	*lvl;
    char    *shlvl;

    shlvl = get_from_env(env, "SHLVL");
	curr_lvl = ft_atoi(shlvl);
    free(shlvl);
	if (!curr_lvl)
	{
		update_env(&env, "SHLVL", "1");
		return ;
	}
	if (curr_lvl < 0)
	{
		update_env(&env, "SHLVL", "1");
		return ;
	}
	if (curr_lvl > 99)
	{
		lvl = ft_itoa(curr_lvl % 100 + 1);
		update_env(&env, "SHLVL", lvl);
		free(lvl);
		return ;
	}
	lvl = ft_itoa(curr_lvl + 1);
	update_env(&env, "SHLVL", lvl);
	free(lvl);
	return ;
}
