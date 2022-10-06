#include "../../includes/parse.h"

static t_list	*create_dummy(char *addr, int size)
{
	t_list	*new;
	char	*dummy;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (NULL);
	if (!addr)
		dummy = NULL;
	else
	{
		dummy = ft_calloc(size + 1, sizeof(char));
		if (!dummy)
		{
			free(new);
			return (NULL);
		}
		ft_strlcpy(dummy, addr, size + 1);
	}
	new->next = NULL;
	new->content = dummy;
	return (new);
}

static int	create_dummys(t_list **dummys, char *line)
{
	t_list	*dummy;
	t_dummy	dummy_info;

	while (is_wspace(*line))
		line++;
	while (*line)
	{
		line += search_dummy(&dummy_info, line);
		dummy = create_dummy(dummy_info.addr, dummy_info.size);
		if (!dummy)
			return (FAIL);
		if (dummy_info.type & ADD_NULL)
		{
			dummy->next = create_dummy(NULL, 1);
			if (!dummy->next)
				return (FAIL);
		}
		ft_lstadd_back(dummys, dummy);
	}
	return (SUCCESS);
}

static t_list	*dummys_to_chunk(t_list **dummy)
{
	t_list	*chunk;
	char	*chunk_prev;

	chunk = ft_calloc(1, sizeof(t_list));
	if (!chunk)
		return (NULL);
	while (*dummy)
	{
		if (!(*dummy)->content)
		{
			*dummy = (*dummy)->next;
			break ;
		}
		chunk_prev = chunk->content;
		chunk->content = ft_strjoin(chunk->content, (*dummy)->content);
		if (!chunk->content)
			return (NULL);
		if (chunk_prev)
			free(chunk_prev);
		*dummy = (*dummy)->next;
	}
	return (chunk);
}

int	split_line(t_list **chunks, t_list **dummys, char *line)
{
	t_list	*chunk;
	t_list	*seek;

	if (create_dummys(dummys, line))
		return (E_CHUNKS);
	seek = *dummys;
	while (seek)
	{
		chunk = dummys_to_chunk(&seek);
		if (!chunk)
			return (E_CHUNKS);
		ft_lstadd_back(chunks, chunk);
	}
	if (!*dummys)
		return (FAIL);
	return (SUCCESS);
}
