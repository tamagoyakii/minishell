#include "../../includes/minishell.h"

/* 이거는 나중에 환경변수 다룰 때 재사용 해도 좋을 것 같아요 */
static char	*get_value(char *key)
{
	t_env	*tmp;

	tmp = g_info.env_list;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*join_path_cmd(char *path, char *cmd)
{
	char	*tmp;

	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (NULL);
	path = ft_strjoin(path, tmp);
	if (!path)
	{
		free(tmp);
		return (NULL);
	}
	return (path);
}

static char	*make_path(t_argv *argv, char **paths)
{
	char		*path;
	struct stat	info;
	int			i;

	i = -1;
	while (paths[++i])
	{
		path = join_path_cmd(paths[i], argv->cmd[0]);
		if (!path)
			exit (FAIL);
		if (stat(path, &info) == SUCCESS)
			return (path);
	}
	return (NULL);
}

char	*get_path(t_argv *argv)
{
	char	*env_path;
	char	**paths;

	env_path = get_value("PATH");
	if (!env_path)
		exit (FAIL);
	paths = ft_split(env_path, ':');
	if (!paths)
		exit (FAIL);
	return (make_path(argv, paths));
}
