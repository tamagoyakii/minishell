# include "../../includes/parse.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->cnt = 0;
	new->cmds = 0;
	return (new);
}

static t_type	*create_type(void)
{
	t_type	*new;

	new = malloc(sizeof(t_type));
	if (!new)
		return (0);
	new->last = NONE;
	new->redir = NONE;
	return (new);
}

int	init_argvs(t_argv **argvs, t_cmd **cmd, t_type **type)
{
	t_argv	*argv;

	*cmd = create_cmd();
	if (!(*cmd))
		return (FAIL);
	*type = create_type();
	if (!(*type))
	{
		free(*cmd);
		return (FAIL);
	}
	argv = create_argv();
	if (!argv)
	{
		free(*cmd);
		free(*type);
		return (FAIL);
	}
	ft_argvadd_back(argvs, argv);
	return (SUCCESS);
}