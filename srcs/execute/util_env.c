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

int	is_valid_key(char *key)
{
	int	i;
	
	i = 0;
	if (!(ft_isalpha(key[i]) || key[i] == '_'))
		return (FAIL);
	i++;
	if (!(ft_isdigit(key[i]) || ft_isalpha(key[i]) || key[i] == '_') && key[i])
	return (SUCCESS);
}

void	print_invalid_error(char *cmd, char *input)
{
	char	*message;
	char	*tmp;

	tmp = ft_strjoin(cmd, ": not a valid identifier");
	if (!tmp)
		ft_error_exit("malloc", strerror(errno), FAIL);
	message = ft_strjoin("export: ", tmp);
	free(tmp);
	ft_putendl_fd(message, 2);
}

void	insert_new_env(t_env *new)
{
	// 정렬 찾아서 삽입
	// 이거 우채한테 코드 있을 것 같은데...
}

void	update_2_arr_env(void)
{
	free_strs(g_info.env);
	g_info.env = make_2_arr_env(g_info.env_list); // 우채 코드
	if(!g_info.env)
		return ; // 우채의 코드에 따라 달라질 예정!
}
