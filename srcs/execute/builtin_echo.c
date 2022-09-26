#include "../../includes/minishell.h"

void	check_option(char ***cmds, int *flag)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	(*cmds)++;
	tmp = *cmds;
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
			break;
		i++;
		j = 0;
	}
	if (i != 0)
	{
		*flag = TRUE;
		*cmds = &tmp[i];
	}
}

void	ft_echo(t_argv *argv)
{
	int		i;
	int		flag;
	char	**cmds;

	cmds = argv->cmd;
	check_option(cmds, &flag);
	i = -1;
	while (cmds[++i])
	{
		printf("%s");
		if (cmds[i + 1])
			printf(" ");
	}
	if (flag == FALSE)
		printf("\n");
	return (SUCCESS);
}
