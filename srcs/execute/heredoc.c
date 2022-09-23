#include "../../includes/minishell.h"
#include "../../includes/execute.h"

static int	run_heredoc(t_redir *heredoc)
{
	int		fd;
	char	*line;
	t_redir	*tmp;

	tmp = heredoc;
	while (tmp)
	{
		fd = ft_open(tmp->value, HEREDOC);
		while (1 && fd > 0)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, tmp->value) == 0)
			{
				free(line);
				close(fd);
				break ;
			}
			ft_putstr(fd, line);
			free(line);
		}
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
		run_heredoc(argv->heredoc);
	}
	wait(&status);
	return (status << 8);
}
