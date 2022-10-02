#include "../../includes/utils.h"

void	free_lst_only(t_list **lst)
{
	t_list	*to_free;
	t_list	*seek;

	seek = *lst;
	while (seek)
	{
		to_free = seek;
		seek = seek->next;
		if (to_free)
			free(to_free);
	}
	*lst = NULL;
}

void	free_content(void *content)
{
	free(content);
}