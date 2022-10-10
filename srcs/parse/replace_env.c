#include "../../includes/parse.h"

char	*find_env(char *key)
{
	t_env	*seek;

	if (*key == '?')
		return (ft_itoa(g_info.last_exit_num));
	seek = g_info.env_list;
	while (seek)
	{
		if (!ft_strcmp(seek->key, key) && seek->value)
			return (ft_strdup(seek->value));
		seek = seek->next;
	}
	return (ft_strdup(""));
}

char	*get_value(char *line)
{
	char	*key;
	char	*value;

	key = ft_substr(line, 1, ft_keylen(line + 1));
	if (!key)
		return (NULL);
	value = find_env(key);
	free(key);
	return (value);
}

int	get_size(char *input)
{
	int		size;
	int		flag;
	char	*env;

	size = 0;
	flag = 0;
	while (*input)
	{
		if (is_variable(input, &flag))
		{
			env = get_value(input);
			if (!env)
				return (FALSE);
			size += ft_strlen(env);
			input += ft_keylen(input + 1) + 1;
			free(env);
		}
		else
		{
			input++;
			size++;
		}
	}
	return (size);
}

static int	init_info(int *flag, int *size, char **line, char *input)
{
	*flag = NONE;
	*size = get_size(input);
	*line = ft_calloc(*size + 1, sizeof(char));
	if (!(*line))
		return (FAIL);
	return (SUCCESS);
}

int	replace_env(char **line, char *input)
{
	char	*env;
	int		size;
	int		flag;

	if (init_info(&flag, &size, line, input))
		return (FAIL);
	while (*input)
	{
		if (is_variable(input, &flag))
		{
			env = get_value(input);
			if (!env)
			{
				free(*line);
				return (FAIL);
			}
			ft_strlcat(*line, env, ft_strlen(env) + ft_strlen(*line) + 1);
			input += ft_keylen(input + 1) + 1;
			free(env);
		}
		else
			ft_strlcat(*line, input++, ft_strlen(*line) + 2);
	}
	return (SUCCESS);
}
