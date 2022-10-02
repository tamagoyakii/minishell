#include "../../includes/execute.h"

static void	wait_childs(int cnt_pipe)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < cnt_pipe + 1)
	{
		if (wait(&status) < 0)
			status = 1;
	}
	if (status > 1)
		status = status >> 8;
	g_info.last_exit_num = status;
}

static void run_execve_proc(t_argv *argv)
{
	char	*path;

	path = get_path(argv->cmd);
	if (!path)
		ft_error_exit(argv->cmd[0], "command not found", ERR_CMD_NOT_FOUND);
	if (execve(path, argv->cmd, g_info.env) == -1)
		ft_error_exit(argv->cmd[0], strerror(errno), FAIL);
}

static void	run_child_proc(t_argv *argv, int **pipes, int i)
{
	set_child_signal();
	set_stdin_pipe(pipes, i - 1);
	set_stdout_pipe(argv, pipes, i);
	set_stdin_redir(argv);
	set_stdout_redir(argv);
	if (is_builtin(argv->cmd) == TRUE)
		run_builtin_proc(argv->cmd);
	else
		run_execve_proc(argv);
}

void	run_fork(t_argv *argv, pid_t *pids, int **pipes, int cnt_pipe)
{
	int		i;
	t_argv	*tmp;

	i = -1;
	tmp = argv;
	while (++i < cnt_pipe + 1)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			run_child_proc(tmp, pipes, i);
		if (pids[i] < 0)
		{
			ft_error("fork", strerror(errno), FAIL);
			break ;
		}
		tmp = tmp->next;
	}
	close_pipes(pipes);
	wait_childs(cnt_pipe);
}
