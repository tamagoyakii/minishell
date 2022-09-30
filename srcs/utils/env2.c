#include "../../includes/minishell.h"

void	make_env_arr(void)
{
	t_env	*env_lst;
	char	**env_arr;
	int		lst_size;
	int		i;

	free_strs(g_info.env);
	lst_size = get_env_list_size();
	env_lst = g_info.env_list;
	i = 0;
	env_arr = (char **)ft_malloc(sizeof(char *) * (lst_size + 1));
	while (env_lst)
	{
		if (env_lst->value)
		{
			env_arr[i] = ft_strjoin_3(env_list->key, "=", env_lst->value);
			i++;
		}
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

void	add_env(t_env **lst, char *env)
{
	t_env	*new;
	t_env	*tmp;
	char	*str;

	tmp = *lst;
	if (!tmp)
	{
		tmp = make_env(env);
		tmp->next = *lst;
		tmp->prev = NULL;
		*lst = tmp;
		return ;
	}
	while (tmp->next && ft_strcmp(tmp->key, env) < 0)
		tmp = tmp->next;
	new = make_env(env);
	insert_new_env(lst, tmp, new, env);
}

/* 맨 처음 시작시 char *envp[] -> list 만들어줌 */
void	init_env(char **env)
{
	int		i;
	t_env	*head;

	i = -1;
	head = NULL;
	while (env[++i])
		add_env(&head, env[i]);
	g_info.env_list = head;
	make_env_arr();
}