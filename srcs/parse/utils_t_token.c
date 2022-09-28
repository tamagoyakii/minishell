# include "../../includes/parse.h"

t_token	*create_token(int type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_type));
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

t_cmd	*create_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->cnt = 0;
	new->cmds = 0;
	return (new);
}