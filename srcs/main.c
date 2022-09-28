/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wochae <wochae@studnet.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:32:12 by jihyukim          #+#    #+#             */
/*   Updated: 2022/09/28 12:22:26 by wochae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

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
	set_signal(SHE,SHE);// signal.c 는 후술 작성 완!
	// g_state_code = 0;
	(void)ac;
	(void)av;
}

int	main(int ac, char *av[], char *envp[])
{
	char		*line;
	t_argv		*argv;
	t_env		*env;

	main_init(ac, av); // 인자들 초기화
	init_env_list(&env, envp); // 환경변수 초기화
	while (1)
	{
		parse(&argv, env);
			split();
			// 문자열 분할

			// 토큰 생성
			// 인자 생성
			// 구현부 넘기기

	}
	
}
