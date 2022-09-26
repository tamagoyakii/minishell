#include "../../includes/minishell.h"

static void execve_process(t_argv *argv, t_env *env)
{
	char	**envp;
	char	*path;

	path = get_path(argv, env);
	envp = make_2_arr_env(env); /* 우채가 만들어줄 예정 */
	if (!envp)
		exit (FAIL);
	if (!path)
	{
		perror("filename: command not found"); /* 에러 코드 모아서 수정 필요 */
		exit(FAIL);
	}
	if (execve(path, argv->cmd, envp) == -1)
	{
		perror("execve ERROR");
		exit(FAIL);
	}
}

void	child_process(t_argv *argv, t_env *env, int **pipes, int i)
{
	set_child_signal();
	set_stdin_pipe(pipes, i - 1);
	set_stdout_pipe(argv, pipes, i);
	set_stdin_redir(argv);
	set_stdout_redir(argv);
	if (is_builtin(argv->cmd) == TRUE)
	{
		builtin_process(argv->cmd, env);
	}
	else
	{
		execve_process(argv, env);
	}
}
