# include "../../includes/minishell.h"

t_token	*create_token(int type, char *value)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_type));
	if (!new)
		return (FAIL);
	new->type = type;
	new->value = value;
	return (new);
}

void	free_token(void *token)
{
	free(token);
}
