#include "../minishell.h"

void	single_builtin(t_argv *argv, t_env **env)
{
	int	origin_stdin;
	int	origin_stdout;

	origin_stdin = ft_dup(IN);
	origin_stdout = ft_dup(OUT);
	if (set_stdin(argv, 0) || set_stdout(argv, 0))
	{
		single_builtin_error();//에러 처리
		return ;
	}
	builtin_process(argv->cmd, env);
	reset_stdin(origin_stdin);
	reset_stdout(origin_stdout);
}
