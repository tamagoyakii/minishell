#include "../minishell.h"

void	close_pipe(t_pipe pipe, int size)
{
	int	i;

	i = -1;
	while (++i < pipe.size)
	{
		close(pipe.pipe[i][0]);
		close(pipe.pipe[i][1]);
	}
}

void	set_stdin_pipe(t_pipe pipe, int num)
{
	int	i;

	if (num < 0)
		return ;
	i = -1;
	while (++i < pipe.size)
	{
		if (i != num)
			close(pipe.pipe[i][0]);
	}
	ft_dup2(pipe.pipe[num][0], STDIN);
}

void	set_stdout_pipe(t_argv *argv, t_pipe pipe, int num)
{
	int	i;

	if (!argv->next)
		return ;
	i = -1;
	while (++i < pipe.size)
	{
		if (i != num)
			close(pipe.pipe[i][1]);
	}
	ft_dup2(pipe.pipe[num][1], STDOUT);
}