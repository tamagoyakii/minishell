# include "../includes/minishell.h"

static int	parse_argvs(t_argv *argvs, t_list *chunks)
{
	t_list	*tokens;

	if (create_tokens(chunks, &tokens))
		return (FAIL);
	free_lst(chunks);
	if (create_argvs(argvs, tokens))
		return (FAIL);
	return (SUCCESS);
}

static void read_input(char **line)
{
	while(1)
	{
		*line = readline("minishell $ ");
		if (!*line)
			continue;	
		if (*line != '\0')
			free(*line);
		add_history(line);
		if (!is_whitespace(line))
			continue;
	}
}

void	parse(t_argv **argv, t_env *env)
{
	char	*line;
	char	*input;
	t_list	*chunks;
	// 우채꺼
	while(1)
	{
		// 우채님 소스
		read_input(&input);
		line = replace_env(input); // line을 읽어서 존재하는 환경변수를 치환한 다음, line에 변경된 값을 덮어쓴다. 그리고 이전 주소 해제
		// 동현이꺼
		split_line(&chunks, line);
		// 지현이꺼 parse_argvs(argvs, chunks);
		parse_argvs(argv, chunks);
		break ;
	}
}
