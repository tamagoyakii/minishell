#include "../includes/minishell.h"

/* calloc(size, n) 쓰는거 괜찮나? */

static char **make_2_arr_env(t_env *env) // 스태틱 함수에 필드 변수들은 다 0으로 초기화 되나요?
{
	// 자배용 이중 key:value
	t_env	*head; // 없어도 될 듯
	char	**arr_env;
	int		i;

	head = env; // 주소 기억하려고
	arr_env = (char	*)ft_calloc(sizeof(char *), 2); // 주소만 기억하려면 이게 맞나? 몰라~ key, value 이렇게 필요한거 아녀?
	i = 0;
	while(head) // head 대신 env해도 됨.
	{
		arr_env[0] = head->key;
		arr_env[1] = head->value;
		head = head->next;
	} // 이래도 되나 싶네.
	return arr_env; // 이거 주소값일텐데 또 발록해야되는지?
}

char	*get_env_key(char *key_value)
{
	size_t	i;
	size_t	len;
	char	*key;

	len = 0;
	while (key_value[len] != 0 && key_value[len] != '=')
		++len;
	if (key_value[len] == '\0')
		return (NULL);
	key = (char *)ft_calloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		key[i] = key_value[i];
		++i;
	}
	key[i] = 0;
	return (key);
}

char	*get_env_value(char *key_value)
{
	size_t	i;
	size_t	len;
	char	*value;

	len = 0;
	while (key_value[len] != 0 && key_value[len] != '=')
		++key_value;
	if (key_value[len] == 0)
		return (NULL);
	len = ft_strlen(++key_value);
	value = (char *)ft_calloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		value[i] = key_value[i];
		++i;
	}
	value[i] = 0;
	return (value);
}

t_env	*compare_env_key(t_env *env_head, char *key)
{
	t_env	*cur;

	cur = env_head;
	while (cur->key != 0 && ft_strncmp(key, cur->key, ft_strlen(cur->key)))
		cur = cur->next;
	return (cur);
}

t_env	*new_env(char *key_value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (key_value == NULL)
	{
		new->key = NULL;
		new->value = NULL;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		new->key = get_env_key(key_value);
		if (new->key == NULL)
			return (NULL);
		new->value = get_env_value(key_value);
		if (new->value == NULL)
			return (NULL);
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

int	init_env_list(t_env *cur, char **envp)
{
	size_t	i;
	t_env	*new;
	t_env	*head;

	i = 0;
	// head = cur; 여기 말고
	cur->key = get_env_key(envp[i]);
	if (cur->key == NULL)
		return (-1);
	cur->value = get_env_value(envp[i]);
	if (cur->value == NULL)
		return (-1);
	cur->next = 0;
	cur->prev = 0;
	head = cur; // 여기가 맞지 않나 ?
	while (envp[++i])
	{
		new = new_env(envp[i]);
		if (new == NULL)
			return (-1);
		cur->next = new;
		new->prev = cur;
		cur = cur->next;
	}
	new = new_env(NULL);
	new->prev = cur;
	cur->next = new;
	make_2_arr_env(cur); // 노드 제일 첫 번째를 이중배열 함수에 보내준다.
	return (0);


}
