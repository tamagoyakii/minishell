/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:58:59 by jihyukim          #+#    #+#             */
/*   Updated: 2022/10/02 16:29:31 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;

	if (s1 == 0 && s2 == 0)
		return (0);
	if (s1 == 0)
		return (ft_strdup(s2));
	if (s2 == 0)
		return (ft_strdup(s1));
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (0);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	while (*s2)
	{
		ret[i++] = *s2;
		s2++;
	}
	ret[i] = 0;
	return (ret);
}
