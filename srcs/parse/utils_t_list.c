# include "../../includes/minishell.h"

void	free_lst_only(t_list *lists)
{
	t_list	*to_free;

	while (lists)
	{
		to_free = lists;
		lists = lists->next;
		if (to_free)
			free(to_free);
	}
}
