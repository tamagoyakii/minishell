#include "../../includes/minishell.h"
#include "../../includes/execute.h"

void	init_execute(int *cnt_pipe, pid_t **pids, t_pipe *pipes, t_argv *argv)
{
	set_pipe_num(&cnt_pipe, argv);
	set_pids(&pids, cnt_pipe);
	set_pipe(pipes, cnt_pipe);
}

void	end_execute(int cnt_pipe, pid_t **pids, t_pipe pipes, t_argv *argv)
{
	wait_childs(pids, cnt_pipe); // -> exit status 변경해줘야함 "$?"
	close_pipe(pipes, cnt_pipe);
	free_pids(pids, cnt_pipe);
	free_pipe(pipes, cnt_pipe);
	free_argv(argv);
}

void	execute(t_argv *argv, t_env **env)
{
	int		i;
	int		cnt_pipe;
	t_pipe	pipes;
	pid_t	*pids;

	if (make_heredoc(argv) == FAIL)
		return (free_argv(argv));	// FAIL일 경우 할당 해제 필요
	init_execute(&cnt_pipe, &pids, &pipes, argv);
	i = -1;
	if (cnt_pipe == 0 && is_builtin(argv->cmd[0]) == SUCCESS)
		single_builtin(argv, env);
	else
	{
		while (++i < cnt_pipe + 1)
		{
			pids[i] = ft_fork(pids, i);
			if (pids[i] == 0)
			{
				child_process(argv, pipes, i, env);
			}
			argv = argv->next;
		}
	}
	end_execute(cnt_pipe, &pids, pipes, argv);
}
