#include "../../includes/minishell.h"

int	set_stdin_redir(t_argv *argv)
{
	int		fd;
	t_type	*tmp;

	tmp = argv->in;
	if (!tmp)
		return (SUCCESS);
	while (tmp)
	{
		fd = ft_open(tmp->value, IN);
		if (fd < 0)
			return (FAIL);
		tmp = tmp->next;
		if (tmp)
			close(fd);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

void	reset_stdin(int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	set_stdout_redir(t_argv *argv)
{
	int		fd;
	t_type	*tmp;

	tmp = argv->out;
	if (!tmp)
		return (SUCCESS);
	while (tmp)
	{
		if (tmp->type == T_OUT)
			fd = ft_open(tmp->value, T_OUT);
		if (tmp->type == A_OUT)
			fd = ft_open(tmp->value, A_OUT);
		if (fd < 0)
			return (FAIL);
		tmp = tmp->next;
		if (tmp)
			close(fd);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

void	reset_stdout(int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
