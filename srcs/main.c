# include "../includes/minishell.h"
# include "../includes/execute.h"
# include "../includes/parse.h"
# include "../includes/utils.h"

t_info g_info;

int	is_whitespace(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
		{
			return (0);
		}
		line++;
	}
	return (1);
}

void	main_init(int ac, char *av[])
{
	struct termios	term;

	if (ac != 1)
		printf("argument input error");
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// set_signal(SHE,SHE); // signal.c 는 후술 작성 완!
	// g_state_code = 0;
	(void)ac;
	(void)av;
}

int	main(int ac, char *av[], char *envp[])
{
	t_argv		*argvs;

	main_init(ac, av); // 인자들 초기화
	//init_env_list(&env, envp); // 환경변수 초기화
	init_env(envp);
	argvs = NULL;
	while (1)
	{
		parse(&argvs);
		execute(argvs);
	}
}
