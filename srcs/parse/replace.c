#include "../../includes/parse.h"

# define NONE 0

static char	*find_env(char *key)
{
	t_env	*tmp;
	char	*finded;

	finded = NULL;
	if (*key == '?')
		finded = ft_itoa(g_info.last_exit_num);
	tmp = g_info.env_list;
	while (tmp && !finded)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			finded = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (!finded)
		finded = ft_strdup("");
	return (finded);
}

static int	ft_keylen(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

char	*get_value(char *line)
{
	char	*key;
	char	*value;

	key = ft_substr(line, 1, ft_keylen(line + 1));
	if (!key)
		return (NULL);
	value = find_env(key);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	free(key);
	return (value);
}

static int	is_variable(char *line, int *flag)
{
	if (*line == '\"')
		*flag ^= D_QUOTE;
	if (!(*flag & D_QUOTE) && *line == '\'')
		*flag ^= S_QUOTE;
	if (*line == '$' && !(*flag & S_QUOTE))
	{
		if (ft_isalnum(*(line + 1)) || *(line + 1) == '_')
			return (TRUE);
		if (*(line + 1) == '?')
			return (TRUE);
	}
	return (FALSE);
}

int	get_size(char *line)
{
	int		size;
	int		flag;
	char	*env;

	size = 0;
	flag = 0;
	while (*line) // 문자를 확인해서 치환 또는 따옴표 일 때
	{
		if (is_variable(line, &flag))
		{
			env = get_value(line);
			if (!env)
				return (FALSE);
			size += ft_strlen(env);
			line += ft_strlen(env) + 1;
			free(env);
		}
		else
		{
			line++;// + 그 다음 문자열 붙이기.
			size++;
		}
	}
	return (size);
}

char	*replace_env(char *line)
{
	char		*dst;
	char		*env;
	int			size;
	int			flag;

	flag = NONE;
	size = get_size(line);
	dst = ft_calloc(size + 1, sizeof(char));
	if (!dst)
		return (NULL);
	while (*line)
	{
		if (is_variable(line, &flag))
		{
			env = get_value(line);
			if (!env)
			{
				free(dst);
				return (NULL);
			}
			ft_strlcat(dst, env, ft_strlen(env) + ft_strlen(dst) + 1);
			line += ft_keylen(line + 1) + 1;
			free(env);
		}
		else
			ft_strlcat(dst, line++, ft_strlen(dst) + 2);
	}
	return (dst);
}
