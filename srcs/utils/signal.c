#include "../../includes/utils.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	hdoc_sigint_handler(int signo)
{
	(void)signo;
	ft_putendl_fd("", STDOUT_FILENO);
	exit(FAIL);
}

void	ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	default_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_info.last_exit_num = FAIL;
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	main_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
