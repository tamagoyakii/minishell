# include "../../includes/minishell.h"

t_argv	*add_argv(t_argv *prev)
{
	t_argv	*new;

	new = (t_argv *)malloc(sizeof(t_argv));
	if (!new)
		return (0);
	prev->next = new;
	new->next = 0;
	return (new);
}

t_type	*add_type(t_type *prev, int type, char *value)
{
	t_type	*new;

	new = (t_type *)malloc(sizeof(t_type));
	if (!new)
		return (0);
	new->type = type;
	new->value = value;
	prev->next = new;
	new->next = 0;
	return (new);
}
