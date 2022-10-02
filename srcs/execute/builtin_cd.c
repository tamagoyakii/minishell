#include "../../includes/execute.h"
#include <limits.h>

static void	update_env_pwds(char *cwd)
{
	t_env	*old_pwd;
	t_env	*pwd;

	old_pwd = get_env("OLDPWD");
	pwd = get_env("PWD");
	if (old_pwd)
	{
		free(old_pwd->value);
		if (!pwd)
			old_pwd->value = ft_strdup("");
		else
			old_pwd->value = ft_strdup(pwd->value);
		if (!old_pwd->value)
			ft_error_exit("malloc", strerror(errno), FAIL);
	}
	if (pwd)
	{
		free(pwd->value);
		pwd->value = ft_strdup(cwd);
		if (!pwd->value)
			ft_error_exit("malloc", strerror(errno), FAIL);
	}
}

void	ft_cd(char **cmd)
{
	char	cwd[PATH_MAX];
	
	if (!cmd[1])
		return ;
	if (cmd[2])
	{
		ft_error("cd", "too many arguments", FAIL);
		return ;
	}
	if (chdir(cmd[1]) != SUCCESS)
	{
		ft_error("cd", strerror(errno), FAIL);
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_error("cd", strerror(errno), FAIL);
		return ;
	}
	update_env_pwds(cwd);
	make_env_arr();
}
