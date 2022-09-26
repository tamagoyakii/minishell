#include "../../includes/minishell.h"

void	close_pipe(int **pipes)
{
	int	i;

	i = -1;
	while (pipes[++i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void	set_stdin_pipe(int **pipes, int num)
{
	int	i;

	if (num < 0)
		return ;
	i = -1;
	while (pipes[++i])
	{
		if (i != num)
			close(pipes[i][0]);
	}
	dup2(pipes[num][0], STDIN_FILENO);
}

void	set_stdout_pipe(t_argv *argv, int **pipes, int num)
{
	int	i;

	if (!argv->next)
		return ;
	i = -1;
	while (pipes[++i])
	{
		if (i != num)
			close(pipes[i][1]);
	}
	dup2(pipes[num][1], STDOUT_FILENO);
}