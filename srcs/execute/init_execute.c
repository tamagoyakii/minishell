#include "../../includes/minishell.h"

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

void	set_pids(pid_t **pids, int cnt_pipe)
{
	*pids = ft_malloc(sizeof(pid_t) * (cnt_pipe + 1));
}

void	set_pipes(int ***pipes, int cnt_pipe)
{
	int	i;

	*pipes = (int **)ft_malloc(sizeof(int *) * (cnt_pipe + 1));
	*pipes[cnt_pipe] = NULL;
	i = -1;
	while (++i < cnt_pipe)
		*pipes[i] = (int *)ft_malloc(sizeof(int) * 2);
	i = -1;
	while (++i < cnt_pipe)
		pipe(*pipes[i]);
}
