#include "../../includes/minishell.h"
#include "../../includes/utils.h"

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

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*full_str;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		ft_error_exit("malloc", strerror(errno), FAIL);
	full_str = ft_strjoin(tmp, s3);
	free(tmp);
	if (!full_str)
		ft_error_exit("malloc", strerror(errno), FAIL);
	return (full_str);
}
