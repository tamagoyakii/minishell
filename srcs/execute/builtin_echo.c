#include "../../includes/execute.h"

static void	change_flag(char ***cmd, int *flag, char **tmp, int i)
{
	if (i != 0)
	{
		*flag = TRUE;
		*cmd = &tmp[i];
	}
}

static void	check_option(char ***cmd, int *flag)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	(*cmd)++;
	tmp = *cmd;
	*flag = FALSE;
	while (tmp[i] && tmp[i][j] == '-')
	{
		if (tmp[i][j] == '-')
		{
			j++;
			while (tmp[i][j] == 'n')
				j++;
		}
		if (tmp[i][j])
			break ;
		i++;
		j = 0;
	}
	change_flag(cmd, flag, tmp, i);
}

void	ft_echo(char **cmd)
{
	int		i;
	int		flag;

	check_option(&cmd, &flag);
	i = -1;
	while (cmd[++i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag == FALSE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_info.last_exit_num = SUCCESS;
}
