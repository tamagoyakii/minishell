/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:38:12 by jihyukim          #+#    #+#             */
/*   Updated: 2022/01/28 18:35:50 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_count(int n)
{
	int			count;
	long long	m;

	count = 0;
	m = n;
	if (m < 0)
	{
		count++;
		m *= -1;
	}
	while (m > 0)
	{
		count++;
		m /= 10;
	}
	return (count);
}

static void	digit_copy(char *ret, int n, int count)
{
	long long	m;

	m = n;
	if (m < 0)
	{
		*ret = '-';
		m *= -1;
	}
	*(ret + count--) = 0;
	while (m > 0)
	{
		*(ret + count) = m % 10 + 48;
		m /= 10;
		count--;
	}
}

char	*ft_itoa(int n)
{
	int		count;
	char	*ret;

	if (n == 0)
	{
		ret = (char *)malloc(sizeof(char) * 1 + 1);
		*ret = '0';
		*(ret + 1) = 0;
	}
	else
	{
		count = digit_count(n);
		ret = (char *)malloc(sizeof(char) * digit_count(n) + 1);
		if (!ret)
			return (0);
		digit_copy(ret, n, count);
	}
	return (ret);
}
