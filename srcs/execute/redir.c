#include "../../includes/minishell.h"
#include "../../includes/execute.h"

int	set_stdin_redir(t_argv *argv)
{
	int		fd;
	int		flag;
	t_redir	*tmp;

	flag = 0;
	tmp = argv->in;
	while (tmp)
	{
		if (tmp->r_type == INPUT)
			fd = ft_open(tmp->value, INPUT);
		if (tmp->r_type == HEREDOC)
			fd = ft_open(tmp->value, HEREDOC);
		tmp = tmp->next;
		if (tmp)
			close(fd);
	}
	ft_dup2(fd, STDIN_FILENO);
	return (g_error.errno);
}

void	reset_stdin(int fd)
{
	ft_dup2(fd, STDIN_FILENO);
}


int	set_stdout_redir(t_argv *argv)
{
	int		fd;
	t_redir	*tmp;

	tmp = argv->out;
	while (tmp)
	{
		if (tmp->r_type == T_OUT)
			fd = ft_open(tmp->value, T_OUT);// 옵션 수정 필요, 실험 요망
		if (tmp->r_type == A_OUT)
			fd = ft_open(tmp->value, A_OUT);
		tmp = tmp->next;
		if (tmp)
			close(fd);
	}
	ft_dup2(fd, STDOUT_FILENO);
	return (g_error.errno);
}

void	reset_stdout(int fd)
{
	ft_dup2(fd, STDOUT_FILENO);
}