#include "../../includes/execute.h"
#include <termios.h>

static int	init_execute(int *cnt, pid_t **pids, int ***pipes, t_argv *argv)
{
	*pids = NULL;
	*pipes = NULL;
	set_pipe_cnt(cnt, argv);
	set_pids(pids, *cnt);
	if (*cnt > 0)
	{
		if (set_pipes(pipes, *cnt) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

static void	end_execute(pid_t *pids, int **pipes, t_argv *argv)
{
	free(pids);
	free_pipes(pipes);
	unlink_hdoc(argv);
	free_argv(argv);
}

static void	set_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	execute(t_argv *argv)
{
	int		cnt_pipe;
	int		**pipes;
	pid_t	*pids;

	if (check_heredoc(argv) == FAIL)
		return (free_argv(argv));
	set_echoctl();
	if (init_execute(&cnt_pipe, &pids, &pipes, argv) == FAIL)
	{
		g_info.last_exit_num = FAIL;
		return (end_execute(pids, pipes, argv));
	}
	if (cnt_pipe == 0 && is_builtin(argv->cmd) == TRUE)
		single_builtin(argv);
	else
		run_fork(argv, pids, pipes, cnt_pipe);
	end_execute(pids, pipes, argv);
}
