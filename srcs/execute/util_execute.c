#include "../../includes/minishell.h"
#include <fcntl.h>

int	ft_open(char *file, int type)
{
	int	fd;

	if (type == T_OUT)
		fd = open(file, O_CREAT | O_WRONLY, 0644);
	if (type == A_OUT)
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (type == IN)
		fd = open(file, O_RDONLY);
	if (type == HDOC)
		fd = open(file, O_CREAT | O_WRONLY, S_IRUSR);
	if (fd < 0 && g_info.pid != getpid())
	{
		ft_error_exit(file, strerror(errno), FAIL);
	}
	if (fd < 0)
		return (-1);
	return (fd);
}

int	is_builtin(char **cmd)
{
	int			i;
	const char	*builtins[7] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit"};

	if (!cmd)
		return (FALSE);
	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(*cmd, builtins[i]) == 0)
			return (TRUE);
	}
	return (FALSE);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_error_exit("malloc", strerror(errno), FAIL);
	return (ptr);
}

void	ft_error(char *cmd, char *msg, int err_num)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	g_info.last_exit_num = err_num;
}

void	ft_error_exit(char *cmd, char *msg, int exit_num)
{
	ft_error(cmd, msg, exit_num);
	exit(exit_num);
}
