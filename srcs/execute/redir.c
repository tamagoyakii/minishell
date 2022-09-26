#include "../../includes/minishell.h"

void	set_stdin_redir(t_argv *argv)
{
	int		fd;
	int		flag;
	t_type	*tmp;

	flag = 0;
	tmp = argv->in;
	while (tmp)
	{
		fd = ft_open(tmp->value, IN);
		tmp = tmp->next;
		if (tmp)
			close(fd);
	}
	dup2(fd, STDIN_FILENO);
}

void	reset_stdin(int fd)
{
	dup2(fd, STDIN_FILENO);
}


void	set_stdout_type(t_argv *argv)
{
	int		fd;
	t_type	*tmp;

	tmp = argv->out;
	while (tmp)
	{
		if (tmp->type == T_OUT)
			fd = ft_open(tmp->value, T_OUT);// 옵션 수정 필요, 실험 요망
		if (tmp->type == A_OUT)
			fd = ft_open(tmp->value, A_OUT);
		tmp = tmp->next;
		if (tmp)
			close(fd);
	}
	dup2(fd, STDOUT_FILENO);
}

void	reset_stdout(int fd)
{
	dup2(fd, STDOUT_FILENO);
}