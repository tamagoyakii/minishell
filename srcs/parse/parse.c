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

void	parse(t_argv **argv)
{
	// 우채꺼
	// 동현이꺼
	// 지현이꺼 parse_argvs(argvs, chunks);
}
