#include "../../includes/execute.h"

static int	is_valid_path(char *path)
{
	struct stat	info;

	if (stat(path, &info) == SUCCESS)
		return (TRUE);
	return (FALSE);
}

static char	*make_path(char *cmd, char **paths)
{
	char		*path;
	int			i;

	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin_3(paths[i], "/", cmd);
		if (is_valid_path(path))
			return (path);
	}
	free(path);
	return (NULL);
}

char	*get_path(char *cmd)
{
	t_env	*env_path;
	char	**paths;

	if (is_valid_path(cmd))
			return (cmd);
	env_path = get_env("PATH");
	if (!env_path)
		exit (FAIL);
	paths = ft_split(env_path->value, ':');
	if (!paths)
		exit (FAIL);
	return (make_path(cmd, paths));
}
