#include "../../includes/execute.h"

static void	unlink_heredoc(t_argv *argv)
{
	t_argv	*tmp;
	t_redir	*heredoc;

	tmp = argv;
	while (tmp)
	{
		heredoc = tmp->hdoc;
		while (heredoc)
		{
			unlink(heredoc->value);
			heredoc = heredoc->next;
		}
		tmp = tmp->next;
	}
}

static void	run_heredoc(t_redir *heredoc)
{
	int		fd;
	char	*line;
	t_redir	*tmp;

	tmp = heredoc;
	while (tmp)
	{
		unlink(tmp->value);
		fd = ft_open(tmp->value, HDOC);
		while (fd > 0)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, &tmp->value[5]) == SUCCESS)
			{
				free(line);
				close(fd);
				break ;
			}
			ft_putendl_fd(line, fd);
			free(line);
		}
		close(fd);
		tmp = tmp->next;
	}
}

int	make_heredoc(t_argv *argv)
{
	int		status;
	pid_t	pid;
	t_argv	*tmp;

	tmp = argv;
	pid = fork();
	if (pid == 0)
	{
		set_heredoc_signal();
		while (tmp)
		{
			run_heredoc(tmp->hdoc);
			tmp = tmp->next;
		}
		exit (SUCCESS);
	}
	if (pid < 0)
		ft_error("fork", strerror(errno), FAIL);
	wait(&status);
	status = status >> 8;
	g_info.last_exit_num = status;
	return (status);
}
