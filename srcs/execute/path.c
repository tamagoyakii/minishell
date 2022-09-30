#include "../../includes/execute.h"

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
	t_env	*env_path;
	char	**paths;

	env_path = get_env("PATH");
	if (!env_path)
		exit (FAIL);
	paths = ft_split(env_path->value, ':');
	if (!paths)
		exit (FAIL);
	return (make_path(argv, paths));
}
