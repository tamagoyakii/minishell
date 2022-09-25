#include "../../includes/minishell.h"
#include "../../includes/execute.h"

static int	run_heredoc(t_type *heredoc)
{
	int		fd;
	char	*line;
	t_type	*tmp;

	tmp = heredoc;
	while (tmp)
	{
		fd = ft_open(tmp->value, HDOC);
		while (1 && fd > 0)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, tmp->value) == 0)
			{
				free(line);
				close(fd);
				break ;
			}
			ft_putstr(line, fd);
			free(line);
		}
		close(fd);
		tmp = tmp->next;
	}
	exit (SUCCESS);
}

int		make_heredoc(t_argv *argv)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		// set_heredoc_signal();
		run_heredoc(argv->hdoc);
	}
	if (pid < 0)
		return (FAIL);
	wait(&status);
	return (status >> 8);
}
