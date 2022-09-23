#include "../minishell.h"

int	set_stdout(t_argv *argv, int num)
{
	int		fd;
	int		flag;
	t_redir	*tmp;

	flag = 0;
	tmp = argv->out;
	while (tmp)
	{
		if (tmp->r_type == OUTPUT && flag == 0)
			fd = ft_open(tmp->value, O_CREAT|O_WRONLY|O_TRUNC);// 옵션 수정 필요, 실험 요망
		if (tmp->r_type == A_OUTPUT && flag == 0)
			fd = ft_open(tmp->value, O_APPEND);
		// if (fd < 0 && flag == 0)
		// 	set_error(ft_strdup(tmp->value), STD_ERROR);
		tmp = tmp->next;
		if (tmp)
			close(fd);
	}
	ft_dup2(fd, STDOUT);
	return (g_error.errno);
}

void	reset_stdout(int fd)
{
	ft_dup2(fd, STDOUT);
}