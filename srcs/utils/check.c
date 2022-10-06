#include "../../includes/utils.h"

int	is_wspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' \
			|| c == '\f' || c == '\r');
}

int	only_wspace(char *str)
{
	while (*str)
	{
		if (!is_wspace(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
