#include "../../includes/execute.h"

static void	heredoc_signal_handler(int signo)
{
	exit(FAIL);
}

static void	child_signal_handler(int signo)
{
	if (signo == SIGINT)
		ft_putstr_fd("^C\n", 2);
	if (signo == SIGQUIT)
		ft_putstr_fd("^\\Quit: 3\n", 2);
	exit(signo + 128);
}

void	set_heredoc_signal(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signal(void)
{
	signal(-1, child_signal_handler);
}

// 김우채 메인에서 사용하는 시그널 추가
