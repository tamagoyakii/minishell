#include "../../includes/utils.h"
#include <readline/readline.h>
#include <signal.h>

void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	exit(FAIL);
}

static void	sigint_handler(int signo)
{
	pid_t   pid;

    pid = waitpid(-1, NULL, WNOHANG);
    if (pid == -1)
    {
		rl_replace_line("", 0);
        printf("\n"); // 히어독일 경우 개행, 히어독
        rl_on_new_line();
        rl_redisplay();
        g_info.last_exit_num = FAIL;
    }
    else
	{
		g_info.last_exit_num = signo + 128;
        printf("\n");
	}
}

static void	sigquit_handler(int signo)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		g_info.last_exit_num = signo + 128;
		ft_putstr_fd("Quit: ", 1);
		ft_putnbr_fd(signo, 1);
		ft_putendl_fd("", 1);
	}
} 

void	init_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
