#include "../../includes/utils.h"

t_argv	*create_argv(void)
{
	t_argv	*new;

	new = (t_argv *)malloc(sizeof(t_argv));
	if (!new)
		return (0);
	new->in = NULL;
	new->out = NULL;
	new->hdoc = NULL;
	new->next = NULL;
	new->cmd = NULL;
	return (new);
}

void	free_argv(t_argv *argv)
{
	t_argv	*tmp;

	tmp = argv;
	while (argv)
	{
		free_redir(tmp->in);
		free_redir(tmp->out);
		free_redir(tmp->hdoc);
		free_strs(tmp->cmd);
		tmp = argv->next;
		free(argv);
		argv = tmp;
	}
}

t_argv	*ft_argvlast(t_argv *argv)
{
	if (!argv)
		return (0);
	while (argv->next)
		argv = argv->next;
	return (argv);
}

void	ft_argvadd_back(t_argv **argvs, t_argv *new)
{
	t_argv	*last;

	if (!argvs)
		return ;
	if (*argvs)
	{
		last = ft_argvlast(*argvs);
		last->next = new;
	}
	else
		*argvs = new;
}
