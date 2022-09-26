#include "../../includes/minishell.h"

void	init_execute(int *cnt_pipe, pid_t **pids, t_pipe *pipes, t_argv *argv)
{
	set_pipe_num(&cnt_pipe, argv);
	if (*cnt_pipe > 0)
	{
		set_pids(&pids, cnt_pipe);
		set_pipe(pipes, cnt_pipe);
	}
}

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
	g_error.errno = status;
	g_error.last_errno = status;
}

void	end_execute(int cnt_pipe, pid_t **pids, t_pipe pipes, t_argv *argv)
{
	wait_childs(cnt_pipe); // -> exit status 변경해줘야함 "$?"
	close_pipe(pipes, cnt_pipe);
	free(pids);
	free_pipe(pipes.pipe, cnt_pipe);
	free_argv(argv);
}

void	execute(t_argv *argv, t_env *env)
{
	int		i;
	int		cnt_pipe;
	t_pipe	pipes;
	pid_t	*pids;

	if (make_heredoc(argv) == FAIL)
		return (free_argv(argv));	// FAIL일 경우 할당 해제 필요
	init_execute(&cnt_pipe, &pids, &pipes, argv);
	i = -1;
	if (cnt_pipe == 0 && is_builtin(argv->cmd[0]) == SUCCESS)
		single_builtin(argv, env);
	else
	{
		while (++i < cnt_pipe + 1)
		{
			pids[i] = ft_fork(pids, i);
			if (pids[i] == 0)
			{
				child_process(argv, env, pipes, i);
			}
			if (pids[i] < 0)
				perror("ERROR");
			argv = argv->next;
		}
	}
	end_execute(cnt_pipe, pids, pipes, argv);
}
