# include "../../includes/minishell.h"

t_type	*create_type(int type, char *value)
{
	t_type	*new;

	new = malloc(sizeof(t_type));
	if (!new)
		return (FAIL);
	new->type = type;
	new->value = value;
	new->next = 0;
	return (new);
}

t_type	*ft_typelast(t_type *type)
{
	if (!type)
		return (0);
	while (type->next)
		type = type->next;
	return (type);
}

void	ft_typeadd_back(t_type **type, t_list *new)
{
	t_type	*last;

	if (!type)
		return ;
	if (*type)
	{
		last = ft_typelast(*type);
		last->next = new;
	}
	else
		*type = new;
}
