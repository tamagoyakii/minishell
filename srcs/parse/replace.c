# include "../../includes/minishell.h"


static char *get_env_key(char *str, t_env *env) // env 안에 str 해당 key가 존재한다면 value 반환, 존재하지 않는다면 NULL을 반환
{
	return "null";
}
static char	*replace_dollar(char *line, t_env *env)
{
	char	*head;
	char	*str;
	size_t	len;
	
	head = line; // offset 역할 치환 시 갱신.
	while(*line != '\0' && *line != '\'' && *line != '"')
		line++;
	len = line - head; // 해당 문자열에서 치환변수의 끝을 찾는다.
	
	strlcat(str,head,len); // str에 head에서 len 만큼의 문자를 복사 ( 환경변수 key값 찾기 위한 niddle )
	get_env_key(str,env);
	ft_strjoin(str,++head); // 치환될 문자열 다음에 것 저장 (++head) // 치환할 문자열을 반환 : $부터 키 내용 인덱스 다음 번째부터 다음 내용을 join한다.
	
	if(*line == '\'') // 함수 1. 문자의 끝, 2. 큰 따옴표 3. 작은 따옴표
		// 치환한다.
		head = *line;
	return head;
}

char	*replace_env(char *line, t_env *env)
{
	/* 우채꺼 */
	char	*dst;
    char    *src;
	int		flag;

	flag = NONE;
	while (*line)
	{
		enum quote;
		if (*line == '\'')
			flag ^= QUOTE;
		if ( *line == '$' && !(flag & QUOTE)) // $가 있고, 작은 따옴표가 감싸져 있다 ( 넘어간다 ). 작은 따옴표가 마치지 않았다 ( 치환 해야한다. )
		{
            src = replace_dollar(line, env);
            ft_strjoin(dst,src);
        }
		// + 그 다음 문자열 붙이기.
	}

	return ;
}
