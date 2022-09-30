# include "../../includes/parse.h"

int	is_pipe(char *input)
{
	if (ft_strcmp(input, "|"))
		return (0);
	return (1);
}

int	is_redir(char *chunk)
{
	int	redir;

	redir = NONE;
	if (!ft_strcmp(chunk, ">"))
		redir = T_OUT;
	if (!ft_strcmp(chunk, ">>"))
		redir = A_OUT;
	if (!ft_strcmp(chunk, "<"))
		redir = IN;
	if (!ft_strcmp(chunk, "<<"))
		redir = HDOC;
	return (redir);
}

static t_token	*create_token(int type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->type = type;
	new->value = value;
	return (new);
}

int	create_tokens(t_list *chunks, t_list **tokens)
{
	t_list	*new_lst;
	t_token	*new_token;

	while (chunks)
	{
		if (is_pipe(chunks->content))
			new_token = create_token(PIPE, chunks->content);
		else if (is_redir(chunks->content))
			new_token = create_token(REDIR, chunks->content);
		else
			new_token = create_token(WORD, chunks->content);
		if (!new_token)
			return (FAIL);
		new_lst = ft_lstnew(new_token);
		if (!new_lst)
			return (FAIL);
		ft_lstadd_back(tokens, new_lst);
		chunks = chunks->next;
	}
	return (SUCCESS);
}
