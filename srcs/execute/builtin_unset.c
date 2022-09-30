#include "../../includes/execute.h"

void	ft_unset(char **cmd)
{
	t_env	*delone;
	int		i;
	
	i = 1;
	if (!cmd[i])
		return ;
	while (cmd[i])
	{
		delone = get_env(cmd[i]);
		if (delone)
		{
			delone->prev->next = delone->next;
			delone->next->prev = delone->prev;
			free(delone->key);
			free(delone->value);
			free(delone);
		}
		else
		{
			if (!is_valid_key(cmd[i]))
				print_invalid_key("unset: ", cmd[i]);
		}
		i++;
	}
	make_env_arr();
}