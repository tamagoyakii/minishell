#include "../../includes/parse.h"

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

static int	check_syntax(t_list	*tokens)
{
	t_token	*token;
	int		last_type;

	last_type = NONE;
	while(tokens)
	{
		token = (t_token *)tokens->content;
		if (last_type == NONE && token->type == PIPE)
			return (FAIL);
		if (last_type == REDIR && token->type != WORD)
			return (FAIL);
		if (last_type == PIPE && token->type == PIPE)
			return (FAIL);
		last_type = token->type;
		tokens = tokens->next;
	}
	if (last_type != WORD)
		return (FAIL);
	return (SUCCESS);
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
			return (E_CHUNKS | E_TOKENS);
		new_lst = ft_lstnew(new_token);
		if (!new_lst)
			return (E_CHUNKS | E_TOKENS);
		ft_lstadd_back(tokens, new_lst);
		chunks = chunks->next;
	}
	if (check_syntax(*tokens))
		return (E_CHUNKS | E_TOKENS | E_SYNTAX);
	return (SUCCESS);
}
