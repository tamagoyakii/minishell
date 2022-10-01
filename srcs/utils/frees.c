#include "../../includes/minishell.h"
#include "../../includes/utils.h"

void	free_redir(t_redir *type)
{
	t_redir	*tmp;

	while (type)
	{
		tmp = type->next;
		free(type->value);
		free(type);
		type = tmp;
	}
}

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	if (!strs)
		return ;
	while (strs[++i])
		free(strs[i]);
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
		free_redir(tmp->hdoc);
		free_strs(tmp->cmd);
		tmp = argv->next;
		free(argv);
		argv = tmp;
	}
}
