#include "../../includes/execute.h"

void	ft_unset(char **cmd)
{
	t_env	*del;
	int		i;
	
	i = 0;
	if (!cmd[++i])
		return ;
	while (cmd[++i])
	{
		del = get_env(cmd[i]);
		if (del)
		{
			del->prev->next = del->next;
			del->next->prev = del->prev;
			free(del->key);
			free(del->value);
			free(del);
		}
		else
		{
			if (!is_valid_key(cmd[i]))
				print_invalid_key("unset: ", cmd[i]);
		}
	}
	make_env_arr();
}