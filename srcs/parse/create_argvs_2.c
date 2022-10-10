#include "../../includes/parse.h"

int	put_cmd(t_cmd *cmd, t_argv **argvs)
{
	t_list	*h_cmd;
	char	**arr;
	int		i;

	if (!cmd->cnt)
		return (SUCCESS);
	arr = malloc(sizeof(char *) * (cmd->cnt + 1));
	if (!arr)
		return (FAIL);
	ft_argvlast(*argvs)->cmd = arr;
	h_cmd = cmd->cmds;
	i = -1;
	while (++i < cmd->cnt)
	{
		arr[i] = ft_strdup(cmd->cmds->content);
		if (!arr[i])
			return (FAIL);
		cmd->cmds = cmd->cmds->next;
	}
	arr[i] = NULL;
	ft_lstclear(&h_cmd, free_content);
	cmd->cnt = 0;
	return (SUCCESS);
}

static int	add_pipe(t_argv **argvs, char *value, t_cmd *cmd, t_type *type)
{
	t_argv	*new_argv;

	if (put_cmd(cmd, argvs))
		return (FAIL);
	new_argv = create_argv();
	if (!new_argv)
		return (FAIL);
	ft_argvadd_back(argvs, new_argv);
	free(value);
	type->redir = NONE;
	type->last = PIPE;
	return (SUCCESS);
}

static int	add_redir(t_argv **argvs, char *value, t_type *type)
{
	t_redir	*new;

	type->redir = is_redir(value);
	new = create_redir(type->redir, NULL);
	if (!new)
		return (FAIL);
	if (type->redir == T_OUT || type->redir == A_OUT)
		ft_rediradd_back(&(*argvs)->out, new);
	else
		ft_rediradd_back(&(*argvs)->in, new);
	if (type->redir == HDOC)
	{
		new = create_redir(type->redir, NULL);
		if (!new)
			return (FAIL);
		ft_rediradd_back(&(*argvs)->hdoc, new);
	}
	free(value);
	type->last = REDIR;
	return (SUCCESS);
}

static int	add_word(t_argv **argvs, t_cmd *cmd, char *value, t_type *type)
{
	t_list	*new_cmd;

	if (type->redir == T_OUT || type->redir == A_OUT)
		ft_redirlast((*argvs)->out)->value = value;
	else if (type->redir == IN)
		ft_redirlast((*argvs)->in)->value = value;
	else if (type->redir == HDOC)
	{
		(ft_redirlast((*argvs)->in)->value) = ft_strjoin("/tmp/.0", value);
		(ft_redirlast((*argvs)->hdoc)->value) = ft_strjoin("/tmp/.0", value);
		free(value);
	}
	else
	{
		new_cmd = ft_lstnew(value);
		if (!new_cmd)
			return (FAIL);
		ft_lstadd_back(&cmd->cmds, new_cmd);
		cmd->cnt += 1;
	}
	type->redir = NONE;
	type->last = WORD;
	return (SUCCESS);
}

int	put_argv(t_argv **argvs, t_token *token, t_cmd *cmd, t_type *type)
{
	t_argv	*argv_last;

	argv_last = ft_argvlast(*argvs);
	if (token->type == PIPE)
		return (add_pipe(argvs, token->value, cmd, type));
	if (token->type == REDIR)
		return (add_redir(&argv_last, token->value, type));
	if (token->type == WORD)
		return (add_word(&argv_last, cmd, token->value, type));
	return (FAIL);
}
