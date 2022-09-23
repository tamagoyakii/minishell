/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:42:24 by jihyukim          #+#    #+#             */
/*   Updated: 2022/01/28 18:38:44 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
			i++;
		else
		{
			count++;
			while (*(s + i) != c && *(s + i))
				i++;
		}
	}
	return (count);
}

static void	ret_free(char **ret)
{
	size_t	i;

	i = 0;
	while (*(ret + i))
	{
		free(*(ret + i));
		i++;
	}
	free(ret);
	ret = 0;
}

static int	str_copy(char **ret, char const *si, size_t j, char c)
{
	size_t	len;

	len = 0;
	while (*(si + len) != c && *(si + len))
		len++;
	*(ret + j) = ft_substr(si, 0, len);
	if (!(ret + j))
	{
		ret_free(ret);
		return (0);
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**ret;

	if (!s)
		return (0);
	ret = (char **)malloc(sizeof(char *) * (str_count(s, c) + 1));
	if (!ret)
		return (0);
	i = 0;
	j = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			i += str_copy(ret, s + i, j, c);
			if (!i)
				return (0);
			j++;
		}
		else
			i++;
	}
	*(ret + j) = 0;
	return (ret);
}
