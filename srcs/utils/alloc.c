#include "../../includes/utils.h"
#include <string.h>
#include <errno.h>

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	if (!strs)
		return ;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_error_exit("malloc", strerror(errno), FAIL);
	return (ptr);
}

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*full_str;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		ft_error_exit("malloc", strerror(errno), FAIL);
	full_str = ft_strjoin(tmp, s3);
	free(tmp);
	if (!full_str)
		ft_error_exit("malloc", strerror(errno), FAIL);
	return (full_str);
}
