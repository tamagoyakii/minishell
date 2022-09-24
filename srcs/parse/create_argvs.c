# include "../includes/minishell.h"

int	put_cmd(t_list *cmds, int size, char **cmd)
{
	int	i;

	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (FAIL);
	i = -1;
	while (++i < size)
	{
		cmd[i] = cmds->content;
		cmds = cmds->next;
	}
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

int	add_pipe(t_argv *argvs, t_list *cmds, int *cnt_cmd, int *last_type)
{
	if (*last_type == NONE)
		return (FAIL);
	if (!put_cmd(cmds, cnt_cmd, argvs->cmd))
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
}

int	create_argv(t_argv *argvs, t_type *tokens)
{
	t_list	*cmds;
	int		cnt_cmd;
	int		last_type;
	int		r_type;
	int		res;

	cnt_cmd = 0;
	last_type = NONE;
	while (tokens)
	{
		if (tokens->type == PIPE)
			res = add_pipe(argvs, cmds, &cnt_cmd, &last_type);
		if (tokens->type == REDIR)
		{
			r_type = is_redir(tokens->value);
			res = add_redir(argvs, tokens->value, r_type, &last_type);
		}
		if (tokens->type == WORD)
		{
			res = add_word(argvs, cmds, tokens->value, &last_type);
			cnt_cmd += 1;
		}
		tokens = tokens->next;
	}
}
