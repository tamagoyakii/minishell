#include "../../includes/utils.h"
#include <unistd.h>

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
