# include "../includes/minishell.h"

static int	put_cmd(t_cmd *cmd, char **arr)
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
	arr[i] = 0;
	free_lst(cmd->cmds);
	cmd->cnt = 0;
	return (SUCCESS);
}

static int	add_redir(t_argv *argvs, char *value, int r_type, int *last_type)
{
	t_type	*head;
	t_type	*new;

	if (*last_type != PIPE && *last_type != WORD && *last_type != NONE)
		return (FAIL);
	if (r_type == T_OUT || A_OUT)
		head = argvs->out;
	else
		head = argvs->in;
	new = create_type(r_type, 0);
	if (!new)
		return (FAIL);
	ft_typeadd_back(&head, new);
	if (r_type == HDOC)
		ft_typeadd_back(&argvs->hdoc, new);
	free(value);
	*last_type = r_type;
	return (SUCCESS);
}

static int	add_pipe(t_argv *argvs, t_cmd *cmd, int *last_type)
{
	t_argv	*new_argv;

	if (*last_type != WORD)
		return (FAIL);
	if (!put_cmd(cmd, argvs->cmd))
		return (FAIL);
	*last_type = PIPE;
	new_argv = create_argv();
	if (!new_argv)
		return (FAIL);
	ft_argvadd_back(argvs, new_argv);
	return (SUCCESS);
}

static int	add_word(t_argv *argvs, t_cmd *cmd, char *value, int *last_type)
{
	t_list	*new_cmd;

	if (*last_type == T_OUT || *last_type == A_OUT)
		ft_typelast(argvs->out)->value = value;
	else if (*last_type == IN)
		ft_typelast(argvs->in)->value = value;
	else if (*last_type == HDOC)
	{
		ft_typelast(argvs->in)->value = ft_strjoin("/tmp/", value);
		ft_typelast(argvs->hdoc)->value = ft_strjoin("/tmp/", value);
		free(value);
	}
	else
	{
		new_cmd = ft_lstnew(value);
		if (!new_cmd)
			return (FAIL);
		ft_lstadd_back(cmd->cmds, new_cmd);
		cmd->cnt += 1;
	}
	*last_type = WORD;
	return (SUCCESS);
}

int	create_argvs(t_argv *argvs, t_list *tokens)
{
	t_token	*token;
	t_cmd	*cmd;
	int		last_type;
	int		r_type;
	int		res;

	cmd->cnt = 0;
	last_type = NONE;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		r_type = is_redir(token->value);
		if (token->type == PIPE)
			res = add_pipe(argvs, cmd, &last_type);
		else if (token->type == REDIR)
			res = add_redir(argvs, token->value, r_type, &last_type);
		else if (token->type == WORD)
			res = add_word(argvs, cmd, token->value, &last_type);
		if (res)
			return (FAIL);
		tokens = tokens->next;
	}
	if (last_type == PIPE || r_type != NONE)
		return (FAIL);
	return (SUCCESS);
}
