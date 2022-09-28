#include "../../includes/minishell.h"
#include <limits.h>

static void	update_env_pwds(void)
{
	char	cwd[PATH_MAX];
	t_env	*old_pwd;
	t_env	*pwd;

	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_error("cd", strerror(errno), FAIL);
		return ;
	}
	old_pwd = get_env("OLDPWD");
	pwd = get_env("PWD");
	if (old_pwd)
	{
		free(old_pwd->value);
		if (!pwd)
			old_pwd->value = strdup("");
		else
			old_pwd->value = strdup(pwd->value);
	}
	if (pwd)
	{
		free(pwd->value);
		pwd->value = cwd;
	}
	update_2_arr_env();
}

void	ft_cd(char **cmd)
{
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
	update_env_pwds();
}
