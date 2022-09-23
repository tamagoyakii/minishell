/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:09:41 by jihyukim          #+#    #+#             */
/*   Updated: 2022/01/28 18:38:09 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	if (dst > src)
	{
		i = len;
		while (i > 0)
		{
			*(unsigned char *)(dst + i - 1)
				= *(const unsigned char *)(src + i - 1);
			i--;
		}
	}
	else
		dst = ft_memcpy(dst, src, len);
	return (dst);
}
