/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:35:36 by jihyukim          #+#    #+#             */
/*   Updated: 2022/01/28 18:39:38 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 && !set)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(""));
	start = 0;
	while (ft_strchr(set, *(s1 + start)) && *(s1 + start))
		start++;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, *(s1 + end)) && end)
		end --;
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}
