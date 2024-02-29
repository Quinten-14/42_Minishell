#include "../../include/minishell.h"
#include "../../include/libft.h"

static char *ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

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

char* getProcessID() {
    char buffer[256];
    int fd;
    char    *pidStr;
    char    *end;

    fd = open("/proc/self/status", O_RDONLY);
    if (fd == -1) {
        perror("Error opening /proc/self/status");
        return NULL; // Error
    }
    read(fd, buffer, sizeof(buffer));
    close(fd);
    pidStr = ft_strstr(buffer, "Pid:");
    if (pidStr != NULL) {
        pidStr += 5;
		while (*pidStr == ' ') {
			pidStr++;
		}
		end = pidStr;
		while (*end != '\n') {
			end++;
		}
		*end = '\0';
		return ft_strdup(pidStr);
    }
    return NULL; // Error
}
