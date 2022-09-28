#include "../../includes/minishell.h"

t_env	*get_env(char *key)
{
	t_env	*tmp;

	tmp = g_info.env_list;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_env(void)
{
	// 있던 이중배열 프리해주는 함수 추가 예정
	g_info.env = make_2_arr_env(g_info.env_list);
}
