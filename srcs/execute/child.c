#include "../../includes/minishell.h"

void	wait_childs(int cnt_pipe)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < cnt_pipe)
	{
		if (wait(&status) < 0)
			status = 1;
	}
	if (status > 1)
		status = status >> 8;
	g_info.last_exit_num = status;
}

static void execve_process(t_argv *argv)
{
	char	**envp;
	char	*path;

	path = get_path(argv, env);
	envp = make_2_arr_env(env); /* 우채가 만들어줄 예정 */
	if (!envp)
		exit (FAIL);
	if (!path)
	{
		perror("filename: command not found"); /* 에러 코드 모아서 수정 필요 */
		exit(FAIL);
	}
	if (execve(path, argv->cmd, envp) == -1)
	{
		perror("execve ERROR");
		exit(FAIL);
	}
}

void	child_process(t_argv *argv, int **pipes, int i)
{
	set_child_signal();
	set_stdin_pipe(pipes, i - 1);
	set_stdout_pipe(argv, pipes, i);
	set_stdin_redir(argv);
	set_stdout_redir(argv);
	if (is_builtin(argv->cmd) == TRUE)
		builtin_process(argv->cmd);
	else
		execve_process(argv);
}

void	child_command(t_argv *argv, pid_t *pids, int **pipes, int cnt_pipe)
{
	int		i;
	t_argv	*tmp;

	i = -1;
	tmp = argv;
	while (++i < cnt_pipe + 1)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			child_process(tmp, pipes, i);
		if (pids[i] < 0)
		{
			ft_error("fork", strerror(errno), FAIL);
			break ;
		}
		tmp = tmp->next;
	}
	close_pipe(pipes);
	wait_childs(cnt_pipe);
}
