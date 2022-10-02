#include "../../includes/utils.h"
#include <string.h>
#include <errno.h>

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

char	*make_key(char *cmd)
{
	char	*key;
	char	*tmp;

	tmp = ft_strchr(cmd, '=');
	if (tmp)
		key = ft_substr(cmd, 0, ft_strlen(cmd) - ft_strlen(tmp));
	else
		key = ft_strdup(cmd);
	if (!key)
			ft_error_exit("malloc", strerror(errno), FAIL);
	return (key);
}

void	print_invalid_key(char *cmd, char *input)
{
	char	*message;
	char	*key;

	key = make_key(input);
	message = ft_strjoin_3(cmd, key, ": not a valid identifier");
	ft_putendl_fd(message, 2);
	free(key);
	free(message);
	g_info.last_exit_num = FAIL;
}

int	get_env_list_size(void)
{
	int		i;
	t_env	*env_lst;

	i = 0;
	env_lst = g_info.env_list;
	while (env_lst)
	{
		if (env_lst->value)
			i++;
		env_lst = env_lst->next;
	}
	return (i);
}
