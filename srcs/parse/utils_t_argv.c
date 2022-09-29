# include "../../includes/parse.h"

t_argv	*create_argv(void)
{
	t_argv	*new;

	new = (t_argv *)malloc(sizeof(t_argv));
	if (!new)
		return (0);
	new->in = 0;
	new->out = 0;
	new->hdoc = 0;
	new->next = 0;
	new->cmd = 0;
	return (new);
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
