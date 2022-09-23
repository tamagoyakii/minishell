#include "../minishell.h"

void	execute(t_argv *argv, t_env **env)
{
	int		i;
	int		cnt_pipe;
	t_pipe	pipe;
	pid_t	*pids;

	if (make_heredoc(argv) == FAIL)	// heredoc마다 파일을 만들어가지고 거기다 다~ 써줄거에요. FAIL이 나오는 경우는 open 실패시랑 시그널 처리가 있습니다.
		return ;					// FAIL일 경우 할당 해제 필요
	if (init(&cnt_pipe, &pids, &pipe, argv) == FAIL)
		return ;//프리해주는 함수 추가 필요
	// set_pipe_num(&cnt_pipe);
	// set_pids(&pids, cnt_pipe);
	// set_pipe(&pipe, cnt_pipe);
	i = -1;
	if (cnt_pipe == 0 && is_builtin(argv->cmd[0]))
		single_builtin(argv, env);
	else
	{
		while (++i < cnt_pipe + 1)
		{
			pids[i] = ft_fork(pids, i);
			if (pids[i] == 0)
			{
				child_process(argv, pipe, i, env);
			}
			argv = argv->next;
		}
	}
	close_pipe(pipe, cnt_pipe);
	free_pids(pids, cnt_pipe);
	free_pipe(pipe, cnt_pipe);
	free_argv(argv);
	wait_childs(pids, cnt_pipe);// -> exit status 변경해줘야함 "$?"
}
