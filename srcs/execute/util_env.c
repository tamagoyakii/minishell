#include "../../includes/minishell.h"

t_env	*get_env(char *key)
{
	t_env	*tmp;

	tmp = g_info.env_list;
	while (tmp)
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
		return (FALSE);
	i++;
	while (key[i] && key[i] != '=')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	print_invalid_error(char *cmd, char *input)
{
	char	*message;
	char	*tmp;
	char	*key;

	key = make_key(input);
	tmp = ft_strjoin(key, ": not a valid identifier");
	free(key);
	if (!tmp)
		ft_error_exit("malloc", strerror(errno), FAIL);
	message = ft_strjoin(cmd, tmp);
	free(tmp);
	if (!message)
		ft_error_exit("malloc", strerror(errno), FAIL);
	ft_putendl_fd(message, 2);
	free(message);
	g_info.last_exit_num = FAIL;
}

void	update_2_arr_env(void)
{
	free_strs(g_info.env);
	make_2_arr_env();
}
