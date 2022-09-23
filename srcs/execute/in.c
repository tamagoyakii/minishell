#include "../minishell.h"

int	set_stdin(t_argv *argv, int num)
{
	int		fd;
	int		flag;
	t_redir	*tmp;

	flag = 0;
	tmp = argv[num]->in;
	while (tmp)
	{
		if (tmp->r_type == INPUT)
			fd = ft_open(tmp->value, INPUT);
		if (tmp->r_type == HEREDOC)
			fd = ft_open(tmp->value, HEREDOC);
		// if (fd < 0)
			// set_error(ft_strdup(tmp->value), STD_ERROR);
		tmp = tmp->next;
		if (tmp)
			close(fd);
	}
	ft_dup2(fd, STDIN);
	return (g_error.errno);
}

void	reset_stdin(int fd)
{
	ft_dup2(fd, STDIN);
}
