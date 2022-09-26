#include "../../includes/minishell.h"
#include <fcntl.h>

int	ft_open(char *file, int type)
{
	int	fd;

	if (type == T_OUT)
		fd = open(file, O_CREAT|O_WRONLY, 0644);
	if (type == A_OUT)
		fd = open(file, O_CREAT|O_APPEND|O_WRONLY, 0644);
	if (type == IN)
		fd = open(file, O_RDONLY);
	if (type == HDOC)
		fd = open(file, O_CREAT|O_WRONLY, S_IRUSR);
	if (fd < 0)
	{
		perror(file);
		exit(FAIL);
	}
	return (fd);
}

int	is_builtin(char *cmd)
{
	int			i;
	const char	*builtins[7] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit"};

	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (SUCCESS);
	}
	return (FAIL);
}
