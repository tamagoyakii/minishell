#include "../minishell.h"

void	free_pids(pid_t *pids, int cnt)
{
	int	i;

	i = -1;
	while (++i < cnt)
		free(pids);
}

void	free_pipes(int **pipes, int cnt)
{
	int	i;
	
	i = -1;
	while (++i < cnt)
		free(pipes[i]);
	free(pipes);
}

void	free_argv(t_argv *argv)
{
	t_argv	*tmp;

	tmp = argv;
	while (argv)
	{
		free_redir(tmp->in);
		free_redir(tmp->out);
		free_strs(tmp->cmd);
		tmp = argv->next;
		free(argv);
		argv = tmp;
	}
}