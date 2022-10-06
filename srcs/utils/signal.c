#include "../../includes/utils.h"
#include <readline/readline.h>
#include <signal.h>

void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	exit(FAIL);
}

static void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
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

void	init_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
