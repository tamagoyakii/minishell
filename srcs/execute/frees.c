#include "../../includes/minishell.h"

void	free_pipes(int **pipes, int cnt)
{
	int	i;
	
	i = -1;
	while (++i < cnt)
		free(pipes[i]);
	free(pipes);
}

void	free_redir(t_type *type)
{
	t_type	*tmp;

	while (type)
	{
		tmp = type->next;
		free(type);
		type = tmp;
	}
}

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
	{
		free(strs[i]);
	}
	free(strs);
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