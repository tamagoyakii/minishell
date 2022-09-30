#include "../../includes/minishell.h"

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

static char	*make_key(char *cmd)
{
	char	*key;
	char	*tmp;
	int		i;

	tmp = ft_strchr(cmd, '=');
	if (tmp)
	{
		key = ft_substr(cmd, 0, ft_strlen(cmd) - ft_strlen(tmp));
		if (!key)
			ft_error_exit("malloc", strerror(errno), FAIL);
	}
	else
	{
		key = ft_strdup(cmd);
		if (!key)
			ft_error_exit("malloc", strerror(errno), FAIL);

	}
	return (key);
}

static void	make_new_env(char *cmd)
{
	t_env	*new_env;
	char	*key;
	char	*value;

	key = make_key(cmd);
	value = ft_strchr(cmd, '=');
	new_env->key = key;
	if (value && ++value)
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

	key = make_key(cmd);
	exist = get_env(key);
	if (!exist)
	{
		free(key);
		return (FALSE);
	}
	free(key);
	value = ft_strchr(cmd, '=');
	if (!value && !exist)
		return (FALSE); 
	if (!value && exist)
		return (TRUE);
	free(exist->value);
	exist->value = ft_strdup(++value);
	if (!exist->value)
			ft_error_exit("malloc", strerror(errno), FAIL);
	return (TRUE);
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
			add_one(&g_info.env_list, cmd[i]);
		i++;
	}
	update_2_arr_env();
}
