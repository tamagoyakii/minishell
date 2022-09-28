#include "../../includes/minishell.h"

static void	print_export(void)
{
	t_env	*tmp;

	tmp = g_info.env_list;
	while (tmp->next)
	{
		printf("declare -x %s", tmp->key);
		if (tmp->value)
			printf("=\"%s\"", tmp->value);
		printf("\n");
	}
}

static char	*make_key(char *cmd)
{
	char	*key;
	char	*tmp;

	key = NULL;
	tmp = NULL;
	while (cmd[i] != '=' && cmd[i])
	{
		tmp = key;
		key = strjoin(tmp, cmd[i]);
		if (!key)
			ft_error_exit("malloc", strerror(errno), FAIL);
		free(tmp);
		i++;
	}
	return (key);
}

static void	make_new_env(char *cmd)
{
	t_env	*new_env;
	char	*key;
	char	*value;
	int		i;

	key = make_key(cmd);
	value = ft_strchr(cmd, '=');
	new_env->key = key;
	if (vlaue && ++value)
		new_env->value = value;
	else
		new_env->value = NULL;
	insert_new_env();
}

static int	is_update_env(char *cmd)
{
	t_env	*exist;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = NULL;
	tmp = NULL;
	value = ft_strchr(cmd, '=');
	if (!value)
		return (FAIL); 
	key = make_key(cmd);
	exist = get_env(key);
	if (!exist)
		reuturn (FAIL);
	free(exist->value);
	exist->value = ++value;
	return (SUCCESS);
}

void	ft_export(char **cmd)
{
	t_env	*updone;
	int		i;
	int		j;
	
	i = 1;
	if (!cmd[i])
		return (print_export());
	while (cmd[i])
	{
		if (!is_valid_key(cmd[i]))
			print_invalid_error("export", cmd[i]);
		else if (!is_update_env(cmd[i]))
			make_new_env(cmd[i]);
		i++;
	}
	update_2_arr_env();
}