#include "../../includes/minishell.h"

void	single_builtin(t_argv *argv, t_env *env)
{
	int	origin_stdin;
	int	origin_stdout;

	origin_stdin = dup(STDIN_FILENO);
	origin_stdout = dup(STDOUT_FILENO);
	if (set_stdin_redir(argv) || set_stdout_redir(argv))
	{
		single_builtin_error();//에러 처리
		return ;
	}
	builtin_process(argv->cmd, env);
	reset_stdin(origin_stdin);
	reset_stdout(origin_stdout);
}
