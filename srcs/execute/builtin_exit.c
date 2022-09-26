#include "../../includes/minishell.h"

void	ft_exit(t_argv *argv)
{
	int	i;
	int	exit_num;

	i = 0;
	while (argv->cmd[i])
		i++;
	if (i > 2)
	{
		ft_error("exit", "too many arguments", FAIL);
		return ;
	}
	exit_num = ft_atouc(argv->cmd[i]);
	if (exit_num < 0)
		ft_error("exit", "numeric argument required", ERR_EXIT_NAN);
	if (g_info.pid == getpid())
		printf("exit\n");
	exit(exit_num);
}
