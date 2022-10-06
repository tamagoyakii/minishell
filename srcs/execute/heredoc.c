#include "../../includes/execute.h"
#include "../../includes/parse.h"
#include <readline/readline.h>

void	unlink_heredoc(t_argv *argv)
{
	t_argv	*tmp;
	t_redir	*hdoc;

	tmp = argv;
	while (tmp)
	{
		hdoc = tmp->hdoc;
		while (hdoc)
		{
			unlink(hdoc->value);
			hdoc = hdoc->next;
		}
		tmp = tmp->next;
	}
}

static void	read_for_heredoc(int fd, char *name)
{
	char	*line;
	char	*input;

	while (fd > 0)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, &name[5]) == SUCCESS)
		{
			free(input);
			break ;
		}
		if (replace_env_heredoc(&line, input))
			ft_error_exit("heredoc", "error", 1);
		ft_putendl_fd(line, fd);
		free(line);
		free(input);
	}
}

static void	run_heredoc(t_redir *hdoc)
{
	int		fd;
	t_redir	*tmp;

	tmp = hdoc;
	while (tmp)
	{
		unlink(tmp->value);
		fd = ft_open(tmp->value, HDOC);
		read_for_heredoc(fd, tmp->value);
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
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, heredoc_sigint_handler);
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
