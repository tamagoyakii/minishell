#include "../../includes/minishell.h"
#include "../../includes/execute.h"

void	set_pipe_cnt(int *cnt_pipe, t_argv *argv)
{
	int	i;

	i = 0;
	argv = argv->next;
	while (argv)
	{
		argv = argv->next;
		i++;
	}
	*cnt_pipe = i;
}

void	set_pids(int **pids, int cnt_pipe)
{
	*pids = malloc(sizeof(int *) * (cnt_pipe + 1));
	if (!*pids)
	{
		perror("ERROR");
		exit(FAIL);
	}
}

void	set_pipes(t_pipe *pipes, int cnt_pipe)
{
	int	i;

	pipes->cnt = cnt_pipe + 1;
	pipes->pipe = malloc(sizeof(int *) * cnt_pipe);
	if (!pipes->pipe)
	{
		perror("ERROR");
		exit (FAIL);
	}
	i = -1;
	while (++i < cnt_pipe)
	{
		pipes->pipe[i] = malloc(sizeof(int) * 2);
		if (!pipes->pipe)
		{
			perror("ERROR");
			exit (FAIL);
		}
	}
	while (++i < cnt_pipe)
		pipe(pipes->pipe[i]);
}
