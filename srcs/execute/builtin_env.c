#include "../../includes/minishell.h"

void	ft_env(char **cmd)
{
	t_env	*tmp;

	tmp = g_info.env_list;
	if (cmd[1])
	{
		ft_error("env", "too many arguments", FAIL);
		return ;
	}
	while (tmp->next)
	{
		if (tmp->value)
			printf("%s=%s", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
