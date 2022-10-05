#include "../../includes/parse.h"

int	ft_keylen(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

int	is_variable(char *input, int *flag)
{
	if (*input == '\"')
		*flag ^= D_QUOTE;
	if (!(*flag & D_QUOTE) && *input == '\'')
		*flag ^= S_QUOTE;
	if (*input == '$' && !(*flag & S_QUOTE))
	{
		if (ft_isalnum(*(input + 1)) || *(input + 1) == '_')
			return (TRUE);
		if (*(input + 1) != ' ' && *(input + 1) != '\0')
			return (TRUE);
	}
	return (FALSE);
}
