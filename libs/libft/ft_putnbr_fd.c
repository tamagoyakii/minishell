/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:55:32 by jihyukim          #+#    #+#             */
/*   Updated: 2022/01/28 18:38:34 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_nbr(long long n, int fd)
{
	char	buf;

	if (!(n / 10))
	{
		buf = n + 48;
		write(fd, &buf, 1);
	}
	else
	{
		buf = n % 10 + 48;
		write_nbr(n / 10, fd);
		write(fd, &buf, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	m;

	m = n;
	if (m < 0)
	{
		write(fd, "-", 1);
		m *= -1;
	}
	write_nbr(m, fd);
}
