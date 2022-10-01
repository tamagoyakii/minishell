#include "../../includes/minishell.h"

/* calloc(size, n) 쓰는거 괜찮나? */
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
