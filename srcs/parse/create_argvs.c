# include "../includes/minishell.h"

int	put_cmd(t_cmd *cmd, char **arr)
{
	t_list	*tmp;
	int		i;

	arr = malloc(sizeof(char *) * (cmd->cnt + 1));
	if (!arr)
		return (FAIL);
	tmp = cmd->cmds;
	i = -1;
	while (++i < cmd->cnt)
	{
		arr[i] = tmp->content;
		tmp = tmp->next;
	}
	while (cmd->cmds)
	{
		tmp = cmd->cmds;
		cmd->cmds = cmd->cmds->next;
		free(tmp);
	}
	cmd->cnt = 0;
	return (SUCCESS);
}

int	add_redir(t_argv *argvs, char *value, int r_type, int *last_type)
{
	t_type	*tmp;

	if (*last_type == T_OUT || *last_type == A_OUT
		|| *last_type == IN || *last_type == HDOC)
		return (FAIL);
	if (r_type == T_OUT || A_OUT)
	{
		argvs->out = add_type(argvs->out, r_type, 0);
		if (!argvs->out)
			return (FAIL);
	}
	if (r_type == IN || HDOC)
	{
		argvs->in = add_type(argvs->in, r_type, 0);
		if (!argvs->in)
			return (FAIL);
	}
	if (r_type == HDOC)
	{
		argvs->hdoc = add_type(argvs->hdoc, r_type, 0);
		if (!argvs->hdoc)
			return (FAIL);
	}
	*last_type = r_type;
	return (SUCCESS);
}

int	add_pipe(t_argv *argvs, t_cmd *cmd, int *last_type)
{
	if (*last_type == NONE)
		return (FAIL);
	if (!put_cmd(cmd, argvs->cmd))
		return (FAIL);
	*last_type = PIPE;
	argvs = add_argv(argvs);
	if (!argvs)
		return (FAIL);
	return (SUCCESS);
}

int	add_word(t_argv *argvs, t_list *cmds, char *value, int *last_type)
{
	if (*last_type == T_OUT || *last_type == A_OUT)
		argvs->out->value = value;
	else if (*last_type == IN || *last_type == HDOC)
		argvs->in->value = value;
	else
	{
		if (!ft_lstnew(value))
			return (FAIL);
	}
	if (*last_type == HDOC)
		argvs->hdoc->value = value;
	*last_type = WORD;
	return (SUCCESS);
}

int	create_argv(t_argv *argvs, t_type *tokens)
{
	t_cmd	*cmd;
	int		last_type;
	int		r_type;
	int		res;

	cmd->cnt = 0;
	last_type = NONE;
	while (tokens)
	{
		r_type = is_redir(tokens->value);
		if (tokens->type == PIPE)
			res = add_pipe(argvs, cmd, &last_type);
		else if (tokens->type == REDIR)
			res = add_redir(argvs, tokens->value, r_type, &last_type);
		else if (tokens->type == WORD)
			res = add_word(argvs, cmd, tokens->value, &last_type);
		if (res)
			return (FAIL);
		tokens = tokens->next;
	}
	return (SUCCESS);
}
