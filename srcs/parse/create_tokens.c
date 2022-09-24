# include "../../includes/minishell.h"

int	is_pipe(char *input)
{
	if (ft_strncmp(input, "|", ft_strlen(input)))
		return (0);
	return (1);
}

int	is_redir(char *chunk)
{
	int	redir;

	redir = NONE;
	if (!ft_strncmp(chunk, ">", ft_strlen(chunk)))
		redir = T_OUT;
	if (!ft_strncmp(chunk, ">>", ft_strlen(chunk)))
		redir = A_OUT;
	if (!ft_strncmp(chunk, "<", ft_strlen(chunk)))
		redir = IN;
	if (!ft_strncmp(chunk, "<<", ft_strlen(chunk)))
		redir = HDOC;
	return (redir);
}

int	create_tokens(t_argv *argvs, t_chunk *chunk, t_type *tokens)
{
	char	*content;

	while (chunk->chunks)
	{
		content = chunk->chunks->content;
		if (is_pipe(content))
			tokens = add_type(tokens, PIPE, content);
		else if (is_redir(content))
			tokens = add_type(tokens, REDIR, content);
		else
			tokens = add_type(tokens, WORD, content);
		if (!tokens)
			return (FAIL);
		chunk->chunks = chunk->chunks->next;
	}
	return (SUCCESS);
}

int	parse_tokens(t_argv *argvs, t_chunk *chunk)
{
	t_type	*tokens;

	if (create_tokens(argvs, chunk, tokens))
		return (FAIL);
	if (!create_argvs(argvs, tokens))
		return (FAIL);
	return (SUCCESS);
}
