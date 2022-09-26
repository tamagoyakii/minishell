#include "../../includes/minishell.h"

void	child_process(t_argv *argv, t_env *env, t_pipe pipe, int i)
{
	set_stdin_pipe(pipe, i - 1);
	set_stdout_pipe(argv, pipe, i);
	if (set_stdin(argv) || set_stdout(argv))
		return ;
	if (is_builtin(argv->cmd[0]))
	{
		set_child_signal();
		builtin_process(argv->cmd, env);
	}
	else
	{
		// 명령어 경로찾는 함수 추가
		execve_process(argv, env);
	}
}
