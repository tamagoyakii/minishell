/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyuk <donghyuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:05:26 by donghyuk          #+#    #+#             */
/*   Updated: 2022/10/10 10:54:02 by donghyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	is_pipe(char *value)
{
	if (ft_strcmp(value, "|"))
		return (0);
	return (1);
}

int	is_redir(char *value)
{
	int	redir;

	redir = NONE;
	if (!ft_strcmp(value, ">"))
		redir = T_OUT;
	if (!ft_strcmp(value, ">>"))
		redir = A_OUT;
	if (!ft_strcmp(value, "<"))
		redir = IN;
	if (!ft_strcmp(value, "<<"))
		redir = HDOC;
	return (redir);
}

int	get_token_type(int type)
{
	int	res;

	res = WORD;
	if (type & _REDIR)
		res = REDIR;
	if (type & _PIPE)
		res = PIPE;
	return (res);
}

char	*get_token_value(t_list **dummies)
{
	t_dummy	*dummy;
	char	*value;
	char	*prev_value;

	value = 0;
	while (*dummies)
	{
		dummy = (*dummies)->content;
		if (!dummy->value)
		{
			*dummies = (*dummies)->next;
			break ;
		}
		prev_value = value;
		value = ft_strjoin(value, dummy->value);
		if (!value)
			return (NULL);
		if (prev_value)
			free(prev_value);
		*dummies = (*dummies)->next;
	}
	return (value);
}

t_token	*create_token(int type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->type = type;
	new->value = value;
	return (new);
}
