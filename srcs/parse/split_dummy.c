#include "../../includes/parse.h"

static int	get_read_size(t_dummy dummy, char *line)
{
	int	read_size;

	read_size = line - dummy.addr;
	if (dummy.type & _QUOTE)
		read_size = read_size + 1;
	return (read_size);
}

static int	get_dummy_size(t_dummy dummy, char *line)
{
	int	size;

	size = line - dummy.addr;
	if (dummy.type & (SPACE | _PIPE | _REDIR))
		size = 1;
	else if (dummy.type & _QUOTE && dummy.type & BREAK)
		size = size - 1;
	return (size);
}

static int	get_dummy_type(char c)
{
	int	type;

	if (c == '\'')
		type = _QUOTE | S_QUOTE;
	else if (c == '"')
		type = _QUOTE | D_QUOTE;
	else if (c == '<')
		type = _REDIR | L_REDIR;
	else if (c == '>')
		type = _REDIR | R_REDIR;
	else if (c == '|')
		type = _PIPE;
	else if (c == ' ')
		type = SPACE;
	else
		type = CHAR;
	return (type);
}

static int	update_dummy_type(t_dummy dummy, char line)
{
	if (dummy.type & CHAR && (line == '>' || line == '<' || line == '|'))
		dummy.type ^= ADD_NULL;
	else if (dummy.type & L_REDIR && line != '<')
		dummy.type ^= ADD_NULL;
	else if (dummy.type & R_REDIR && line != '>')
		dummy.type ^= ADD_NULL;
	else if (dummy.type & _PIPE || dummy.type & SPACE)
		dummy.type ^= ADD_NULL;
	return (dummy.type);
}

int	search_dummy(t_dummy *dummy, char *line)
{
	int	read_size;

	dummy->type = get_dummy_type(*line);
	if (dummy->type & _QUOTE)
		line += 1;
	dummy->addr = line;
	while (*line && !(dummy->type & BREAK))
	{
		if (dummy->type & CHAR && (*line == ' ' || *line == '\'' || *line == '"'
				|| *line == '>' || *line == '<' || *line == '|'))
			break ;
		if (dummy->type & S_QUOTE && *line == '\'')
			dummy->type ^= BREAK;
		if (dummy->type & D_QUOTE && *line == '"')
			dummy->type ^= BREAK;
		if (dummy->type & (SPACE | _REDIR | _PIPE) && *(line + 1) != ' ')
			dummy->type ^= BREAK;
		line++;
	}
	read_size = get_read_size(*dummy, line);
	dummy->size = get_dummy_size(*dummy, line);
	dummy->type = update_dummy_type(*dummy, *line);
	return (read_size);
}