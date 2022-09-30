#include "../../includes/minishell.h"

void	make_2_arr_env(void)
{
	t_env	*env_lst;
	char	**env_arr;
	char	*tmp;
	int		size;
	int		i;

	i = 0;
	env_lst = g_info.env_list;
	while (env_lst)
	{
		env_lst = env_lst->next;
		i++;
	}
	size = i;
	env_arr = (char **)ft_malloc(sizeof(char *) * (i + 1));
	env_arr[i] = NULL;
	env_lst = g_info.env_list;
	i = 0;
	while (env_lst)
	{
		if (env_lst->value)
		{
			tmp = ft_strjoin(g_info.env_list->key, "=");
			if (!tmp)
				ft_error_exit("malloc", strerror(errno), FAIL);
			env_arr[i] = ft_strjoin(tmp, env_lst->value);
			if (!env_arr[i])
				ft_error_exit("malloc", strerror(errno), FAIL);
			free(tmp);
			i++;
		}
		env_lst = env_lst->next;
	}
	while (i < size)
		env_arr[i++] = NULL;
	g_info.env = env_arr;
}

void	insert_new_env(t_env **lst, t_env *tmp, t_env *new, char *env)
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

t_env	*new_env_lst(char *env)
{
	t_env	*new;
	char	*str;

	new = (t_env *)ft_malloc(sizeof(t_env));
	str = ft_strchr(env, '=');
	if (str)
		new->key = ft_substr(env, 0, ft_strlen(env) - ft_strlen(str));
	else
		new->key = ft_strdup(env);
	if (!new->key)
		ft_error_exit("malloc", strerror(errno), FAIL);
	if (str)
	{
		new->value = ft_strdup(str + 1);
		if (!new->value)
			ft_error_exit("malloc", strerror(errno), FAIL);
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	add_one(t_env **lst, char *env)
{
	t_env	*new;
	t_env	*tmp;
	char	*str;

	tmp = *lst;
	if (!tmp)
	{
		tmp = new_env_lst(env);
		tmp->next = *lst;
		tmp->prev = NULL;
		*lst = tmp;
		return ;
	}
	while (tmp->next && ft_strcmp(tmp->key, env) < 0)
		tmp = tmp->next;
	new = new_env_lst(env);
	insert_new_env(lst, tmp, new, env);
}

/* 맨 처음 시작시 char *envp[] -> list 만들어줌 */
void	set_env(char **env)
{
	int		i;
	t_env	*head;

	i = -1;
	head = NULL;
	add_one(&head, env[++i]);
	while (env[++i])
		add_one(&head, env[i]);
	g_info.env_list = head;
	make_2_arr_env();
}
