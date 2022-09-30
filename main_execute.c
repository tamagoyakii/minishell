#include "./includes/execute.h"

t_info	g_info;

t_redir	*add_redir(char *file, int type)
{
	t_redir	*tmp;

	tmp = (t_redir *)malloc(sizeof(t_redir));
	tmp->next = NULL;
	tmp->type = type;
	tmp->value = ft_strdup(file);
	return (tmp);
}

void	add_cmds(t_argv **argv, char *cmds)
{
	t_argv	*tmp;

	tmp = *argv;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
	{
		tmp = (t_argv *)malloc(sizeof(t_argv));
		tmp->cmd = ft_split(cmds, ' ');
		tmp->hdoc = NULL;
		tmp->in = NULL;
		// tmp->hdoc = add_redir("/tmp/hi", HDOC);
		// tmp->in = add_redir("/tmp/hi", HDOC);
		tmp->out = NULL;
		tmp->next = NULL;
		*argv = tmp;
	}
	else
	{
		tmp->next = malloc(sizeof(t_argv));
		tmp->next->cmd = ft_split(cmds, ' ');
		// tmp->next->hdoc = add_redir("/tmp/hi", HDOC);
		// tmp->next->in = add_redir("/tmp/hi", HDOC);
		// tmp->next->out = add_redir("out", T_OUT);
		tmp->next->hdoc = NULL;
		tmp->next->in = NULL;
		tmp->next->out = NULL;
		tmp->next->next = NULL;
	}
}

int	main2(int ac, char *av[], char *ev[])
{
	t_argv *argv;

	argv = NULL;
	g_info.pid = getpid();
	init_env(ev);
	while (ac-- > 1)
	{
		add_cmds(&argv, *(++av));
	}
	// execve(ft_strjoin("/bin/", argv->cmd[0]), argv->cmd, g_info.env);
	execute(argv);
	return (0);
}

int	main(int ac, char *av[], char *ev[])
{
	main2(ac, av, ev);
	// system("leaks minishell");
	return (g_info.last_exit_num);
}