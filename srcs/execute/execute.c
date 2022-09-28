#include "../../includes/minishell.h"

int	init_execute(int *cnt_pipe, pid_t **pids, int ***pipes, t_argv *argv)
{
	*pids = NULL;
	*pipes = NULL;
	set_pipe_cnt(cnt_pipe, argv);
	set_pids(pids, *cnt_pipe);
	if (*cnt_pipe > 0)
	{
		if (set_pipes(pipes, *cnt_pipe) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

void	end_execute(pid_t *pids, int **pipes, t_argv *argv)
{
	free(pids);
	free_pipes(pipes);
	unlink_heredoc(argv);
	free_argv(argv);
}

void	execute(t_argv *argv)
{
	int		cnt_pipe;
	int		**pipes;
	pid_t	*pids;

	if (make_heredoc(argv) == FAIL)
		return (free_argv(argv));
	if (init_execute(&cnt_pipe, &pids, &pipes, argv) == FAIL)
		return (end_execute(pids, pipes, argv));
	if (cnt_pipe == 0 && is_builtin(argv->cmd) == TRUE)
		single_builtin(argv);
	else
		child_command(argv, pids, pipes, cnt_pipe);
	end_execute(pids, pipes, argv);
}
