#include "../../includes/execute.h"
#include <unistd.h>

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

void	run_builtin_proc(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == SUCCESS)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "cd") == SUCCESS)
		ft_cd(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == SUCCESS)
		ft_pwd(cmd);
	else if (ft_strcmp(cmd[0], "export") == SUCCESS)
		ft_export(cmd);
	else if (ft_strcmp(cmd[0], "unset") == SUCCESS)
		ft_unset(cmd);
	else if (ft_strcmp(cmd[0], "env") == SUCCESS)
		ft_env(cmd);
	else if (ft_strcmp(cmd[0], "exit") == SUCCESS)
		ft_exit(cmd);
	if (g_info.pid != getpid())
		exit (SUCCESS);
}

void	single_builtin(t_argv *argv)
{
	int	origin_stdin;
	int	origin_stdout;

	origin_stdin = dup(STDIN_FILENO);
	origin_stdout = dup(STDOUT_FILENO);
	if (set_stdin_redir(argv) == FAIL || set_stdout_redir(argv) == FAIL)
	{
		reset_stdin(origin_stdin);
		reset_stdout(origin_stdout);
		return ;
	}
	run_builtin_proc(argv->cmd);
	reset_stdin(origin_stdin);
	reset_stdout(origin_stdout);
}
