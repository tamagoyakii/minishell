#include "../../includes/minishell.h"

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
				print_invalid_error("unset", cmd[i]);
		}
		i++;
	}
	update_2_arr_env();
}