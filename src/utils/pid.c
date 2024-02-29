#include "../../include/minishell.h"
#include "../../include/libft.h"

static char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

char	*get_process_id(void)
{
	char	buffer[256];
	int		fd;
	char	*pid_str;
	char	*end;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening /proc/self/status");
		return (NULL);
	}
	read(fd, buffer, sizeof(buffer));
	close(fd);
	pid_str = ft_strstr(buffer, "Pid:");
	if (pid_str != NULL)
	{
		pid_str += 5;
		while (*pid_str == ' ')
			pid_str++;
		end = pid_str;
		while (*end != '\n')
			end++;
		*end = '\0';
		return (ft_strdup(pid_str));
	}
	return (NULL);
}
