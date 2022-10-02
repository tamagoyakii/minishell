#include "../../includes/execute.h"
#include <limits.h>
#include <unistd.h>

void	ft_pwd(char **cmd)
{
	char	cwd[PATH_MAX];

	if (cmd[1])
	{
		ft_error("pwd", "too many arguments", FAIL);
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_error("pwd", strerror(errno), FAIL);
		return ;
	}
	printf("%s\n", cwd);
}
