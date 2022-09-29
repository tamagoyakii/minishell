# include "../../includes/minishell.h"

t_redir	*create_redir(int redir, char *value)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->type = redir;
	new->value = value;
	new->next = 0;
	return (new);
}

t_redir	*ft_redirlast(t_redir *redir)
{
	if (!redir)
		return (0);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

void	ft_rediradd_back(t_redir **redir, t_redir *new)
{
	t_redir	*last;

	if (!redir)
		return ;
	if (*redir)
	{
		last = ft_redirlast(*redir);
		last->next = new;
	}
	else
		*redir = new;
}
