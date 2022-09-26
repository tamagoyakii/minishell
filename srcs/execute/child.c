#include "../../includes/minishell.h"

static void execve_process(t_argv *argv, t_env *env)
{
	char *str[2];

	str[0] = get_path(argv, env);
	str[1] = NULL;
	if (!str[0])
	{
		perror("filename: command not found"); /* 에러 코드 모아서 수정 필요 */
		exit(FAIL);
	}
	if (execve(str[0], str, NULL) == -1)
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
	if (!argv->cmd)
		exit(SUCCESS);
	if (is_builtin(argv->cmd[0]) == TRUE)
	{
		builtin_process(argv->cmd, env);
	}
	else
	{
		execve_process(argv, env);
	}
}
