#include "../minishell.h"

void	child_process(t_argv *argv, t_pipe pipe, int i, t_env **env)
{
	set_stdin_pipe(pipe, i - 1);
	set_stdout_pipe(argv, pipe, i);
	if (set_stdin(argv, 0) || set_stdout(argv, 0))
		return ;
	if (is_builtin(argv->cmd[0]))
	{
		// set_signal();
		builtin_process(argv->cmd, env);
	}
	else
	{
		// 명령어 경로찾는 함수 추가
		execve_process(argv, env);
	}
}
