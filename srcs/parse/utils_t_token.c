# include "../../includes/parse.h"

t_token	*create_token(int type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->type = type;
	new->value = value;
	return (new);
}

void	free_token(void *token)
{
	free(token);
}
