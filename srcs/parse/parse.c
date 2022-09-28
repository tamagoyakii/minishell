# include "../../includes/parse.h"

void	test_argvs(t_argv **argvs)
{
	int	i = -1;
	int j = -1;
	while (*argvs)
	{
		++i;
		j = -1;
		while ((*argvs)->out)
		{
			printf("out_%d_%d: %d, %s\n", i, ++j, (*argvs)->out->type, (*argvs)->out->value);
			(*argvs)->out = (*argvs)->out->next;
		}
		j = -1;
		while ((*argvs)->in)
		{
			printf("in_%d_%d: %d, %s\n", i, ++j, (*argvs)->in->type, (*argvs)->in->value);
			(*argvs)->in = (*argvs)->in->next;
		}
		j = -1;
		while ((*argvs)->hdoc)
		{
			printf("hdoc_%d_%d: %d, %s\n", i, ++j, (*argvs)->hdoc->type, (*argvs)->hdoc->value);
			(*argvs)->hdoc = (*argvs)->hdoc->next;
		}
		j = -1;
		while ((*argvs)->cmd[++j])
			printf("cmd_%d: %s\n", j, (*argvs)->cmd[j]);
		*argvs = (*argvs)->next;
	}
}

static int	parse_argvs(t_argv **argvs, t_list *chunks)
{
	t_list	*tokens;

	tokens = 0;
	if (create_tokens(chunks, &tokens))
		return (FAIL);
	free_lst_only(&chunks); // 해제 확인해야함
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

void	parse(t_argv **argvs, t_env *env)
{
	t_list	*chunks;
	char	*line;
	char	*input;

	while(1)
	{
		// 우채님 소스
		// read_input(&input);
		// line = replace_env(input); // line을 읽어서 존재하는 환경변수를 치환한 다음, line에 변경된 값을 덮어쓴다. 그리고 이전 주소 해제

		// 동현이꺼
		split_line(&chunks, line);

		// 지현이꺼
		parse_argvs(argvs, chunks);
		// test_argvs(argvs); // argvs 확인용 함수입니다.
		break ;
	}
}
