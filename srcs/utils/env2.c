#include "../../includes/utils.h"
#include <string.h>
#include <errno.h>

void	make_env_arr(void)
{
	t_env	*env_lst;
	char	**env_arr;
	int		lst_size;
	int		i;

	free_strs(g_info.env);
	lst_size = get_env_list_size();
	env_lst = g_info.env_list;
	i = -1;
	env_arr = (char **)ft_malloc(sizeof(char *) * (lst_size + 1));
	while (env_lst)
	{
		if (env_lst->value)
			env_arr[++i] = ft_strjoin_3(env_lst->key, "=", env_lst->value);
		env_lst = env_lst->next;
	}
	env_arr[lst_size] = NULL;
	g_info.env = env_arr;
}

static void	insert_new_env(t_env **lst, t_env *tmp, t_env *new, char *env)
{
	if (ft_strcmp(tmp->key, env) < 0)
	{
		new->next = tmp->next;
		if (new->next)
			new->next->prev = new;
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		new->prev = tmp->prev;
		new->next = tmp;
		if (!tmp->prev)
			*lst = new;
		else
			tmp->prev->next = new;
		tmp->prev = new;
	}
}

t_env	*make_env(char *env)
{
	t_env	*new;
	char	*value;

	new = (t_env *)ft_malloc(sizeof(t_env));
	new->key = make_key(env);
	value = ft_strchr(env, '=');
	if (value)
	{
		new->value = ft_strdup(++value);
		if (!new->value)
			ft_error_exit("malloc", strerror(errno), FAIL);
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	add_env(t_env **lst, char *env)
{
	t_env	*new;
	t_env	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		tmp = make_env(env);
		tmp->next = *lst;
		tmp->prev = NULL;
		*lst = tmp;
		g_info.env_list = *lst;
		return ;
	}
	while (tmp->next && ft_strcmp(tmp->key, env) < 0)
		tmp = tmp->next;
	new = make_env(env);
	insert_new_env(lst, tmp, new, env);
}

void	init_env(char **env)
{
	int		i;
	int		next_leve;
	t_env	*head;
	t_env	*lvl;

	i = -1;
	head = NULL;
	while (env[++i])
		add_env(&head, env[i]);
	lvl = get_env("SHLVL");
	if (lvl)
	{
		next_leve = ft_atoi(lvl->value) + 1;
		free(lvl->value);
		lvl->value = ft_itoa(next_leve);
		if (!lvl->value)
			ft_error_exit("malloc", strerror(errno), FAIL);
	}
	else
		add_env(&head, "SHLVL=1");
	make_env_arr();
}
