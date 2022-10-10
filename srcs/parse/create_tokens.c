#include "../../includes/parse.h"

static t_list	*create_dummy(char *addr, int size, int type)
{
	t_list	*new;
	t_dummy	*dummy;

	dummy = ft_calloc(1, sizeof(t_dummy));
	if (!dummy)
		return (NULL);
	dummy->value = NULL;
	if (addr)
	{
		dummy->type = type;
		dummy->value = ft_calloc(size + 1, sizeof(char));
		if (!dummy->value)
		{
			free(dummy);
			return (NULL);
		}
		ft_strlcpy(dummy->value, addr, size + 1);
	}
	new = ft_lstnew(dummy);
	if (!new)
	{
		free(dummy->value);
		free(dummy);
	}
	return (new);
}

static int	create_dummies(t_list **dummys, char *line)
{
	t_list			*dummy;
	t_dummy_info	dummy_info;

	while (is_wspace(*line))
		line++;
	while (*line)
	{
		line += search_dummy(&dummy_info, line);
		dummy = create_dummy(dummy_info.addr, dummy_info.size, dummy_info.type);
		if (!dummy)
			return (FAIL);
		if (dummy_info.type & ADD_NULL)
		{
			dummy->next = create_dummy(NULL, 1, 0);
			if (!dummy->next)
				return (FAIL);
		}
		ft_lstadd_back(dummys, dummy);
	}
	return (SUCCESS);
}

static t_list	*dummies_to_token(t_list **dummies)
{
	t_list	*res;
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = get_token_type(((t_dummy *)(*dummies)->content)->type);
	token->value = get_token_value(dummies);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	res = ft_calloc(1, sizeof(t_list));
	if (!res)
	{
		free(token->value);
		free(token);
		return (NULL);
	}
	res->content = (void *)token;
	return (res);
}

static int	check_syntax(t_list	*tokens)
{
	t_token	*token;
	int		last_type;

	last_type = NONE;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (last_type == NONE && token->type == PIPE)
			return (FAIL);
		if (last_type == REDIR && token->type != WORD)
			return (FAIL);
		if (last_type == PIPE && token->type == PIPE)
			return (FAIL);
		if (token->type == REDIR && !is_redir(token->value))
			return (FAIL);
		last_type = token->type;
		tokens = tokens->next;
	}
	if (last_type != WORD)
		return (FAIL);
	return (SUCCESS);
}

int	create_tokens(t_list **tokens, t_list **dummys, char *line)
{
	t_list	*token;
	t_list	*seek;

	if (create_dummies(dummys, line))
		return (E_DUMMIES);
	seek = *dummys;
	while (seek)
	{
		token = dummies_to_token(&seek);
		if (!token)
			return (E_DUMMIES | E_TOKENS);
		ft_lstadd_back(tokens, token);
	}
	if (!*dummys)
		return (FAIL);
	if (check_syntax(*tokens))
		return (E_DUMMIES | E_TOKENS | E_SYNTAX);
	return (SUCCESS);
}
