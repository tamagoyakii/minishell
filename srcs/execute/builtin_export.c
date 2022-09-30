#include "../../includes/execute.h"

static void	print_export(void)
{
	t_env	*tmp;

	tmp = g_info.env_list;
	while (tmp)
	{
		printf("declare -x %s", tmp->key);
		if (tmp->value)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

static int	is_update_env(char *cmd)
{
	t_env	*exist;
	char	*key;
	char	*value;

	key = make_key(cmd);
	exist = get_env(key);
	if (!exist)
	{
		free(key);
		return (FALSE);
	}
	free(key);
	value = ft_strchr(cmd, '=');
	if (!value)
		return (TRUE);
	free(exist->value);
	exist->value = ft_strdup(++value);
	if (!exist->value)
			ft_error_exit("malloc", strerror(errno), FAIL);
	free(value);
	return (TRUE);
}

void	ft_export(char **cmd)
{
	int	i;
	
	i = 0;
	if (!cmd[1])
		return (print_export());
	while (cmd[++i])
	{
		if (!is_valid_key(cmd[i]))
			print_invalid_key("export: ", cmd[i]);
		else if (!is_update_env(cmd[i]))
			add_env(&g_info.env_list, cmd[i]);
	}
	make_env_arr();
}
