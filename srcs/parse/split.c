#include "../include/minishell.h"

static int	create_dummy(t_list **dummys, char *addr, int size)
{
	t_list	*new;
	char	*dummy;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (FAIL);
	dummy = malloc(sizeof(char) * (size + 1));
	if (!dummy)
	{
		free(new);
		return (FAIL);
	}
	new->next = NULL;
	new->content = dummy;
	ft_strlcpy(dummy, addr, size + 1);
	ft_lstadd_back(dummys, new);
	return (SUCCESS);
}

static int	check_quote(char **line, int *flag)
{
	if (**line == '\'')
		*flag ^= (QUOTE | NONE);
	else if (**line == '"')
		*flag ^= (DQUOTE | NONE);
	else if (**line == ' ')
		;
	else
		return (0);
	return (1);
}

static int	create_dummys(t_list **dummys, char *line)
{
	int		flag;
	char	*start_line;

	flag = NONE;
	while (line && *line)
	{
		while (flag == NONE && *line == ' ')
			line++;
		if (check_quote(&line, &flag))
			line++;
		start_line = line;
		while (*line)
		{
			if (flag & NONE && (*line == ' ' || *line == '\'' || *line == '"'))
				break ;
			if (flag & QUOTE && *line == '\'')
				break ;
			if (flag & DQUOTE && *line == '"')
				break ;
			line++;
		}
		if (create_dummy(dummys, start_line, line - start_line))
			return (FAIL);
	}
	return (SUCCESS);
}

static t_list	*dummys_to_chunk(t_list **dummy)
{
	t_list	*chunk;
	char	*chunk_prev;
	char	*chunk_content;

	chunk_content = NULL;
	chunk = ft_calloc(1, sizeof(t_list));
	if (!chunk)
		return (NULL);
	while (*dummy)
	{
		if (!ft_strncmp((*dummy)->content, "", 1))
		{
			*dummy = (*dummy)->next;
			break ;
		}
		chunk_prev = chunk_content;
		chunk_content = ft_strjoin(chunk_content, (*dummy)->content);
		if (!chunk_content)
			return (NULL);
		if (chunk_prev)
			free(chunk_prev);
		*dummy = (*dummy)->next;
	}
	chunk->content = chunk_content;
	return (chunk);
}

void	free_dummy(void *content)
{
	free(content);
}

int	split_line(t_list **chunks, char *line)
{
	t_list	*chunk;
	t_list	*dummys;
	t_list	*h_dummys;

	dummys = NULL;
	*chunks = NULL;
	h_dummys = dummys;
	if (create_dummys(&dummys, line))
	{
		// free();
		return (FAIL);
	}
	while (dummys)
	{
		chunk = dummys_to_chunk(&dummys);
		if (!chunk)
		{
			// free();
			return (FAIL);
		}
		ft_lstadd_back(chunks, chunk);
	}
	ft_lstclear(&h_dummys, free_dummy);
	return (SUCCESS);
}
