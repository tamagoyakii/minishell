/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:34:48 by jihyukim          #+#    #+#             */
/*   Updated: 2022/01/28 18:39:41 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	if (!s)
		return (0);
	if (ft_strlen(s) <= start)
	{
		ret = malloc(1);
		*ret = 0;
		return (ret);
	}
	if (ft_strlen(s + start) <= len)
		len = ft_strlen(s + start);
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (!ret)
		return (0);
	i = 0;
	while (*(s + start + i) && i < len)
	{
		*(ret + i) = *(s + start + i);
		i++;
	}
	*(ret + i) = 0;
	return (ret);
}
