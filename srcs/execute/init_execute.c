#include "../../includes/execute.h"

void	set_pipe_cnt(int *cnt_pipe, t_argv *argv)
{
	int		i;
	t_argv	*tmp;

	i = 0;
	if (!argv)
	{
		*cnt_pipe = 0;
		return ;
	}
	tmp = argv->next;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	*cnt_pipe = i;
}

void	set_pids(pid_t **pids, int cnt_pipe)
{
	*pids = ft_malloc(sizeof(pid_t) * (cnt_pipe + 1));
}

int	set_pipes(int ***pipes, int cnt_pipe)
{
	int	i;

	*pipes = (int **)ft_malloc(sizeof(int *) * (cnt_pipe + 1));
	(*pipes)[cnt_pipe] = NULL;
	i = -1;
	while (++i < cnt_pipe)
		(*pipes)[i] = (int *)ft_malloc(sizeof(int) * 2);
	i = -1;
	while (++i < cnt_pipe)
	{
		if (pipe((*pipes)[i]) < 0)
		{
			ft_error("pipe", strerror(errno), FAIL);
			return (FAIL);
		}
	}
	return (SUCCESS);
}
