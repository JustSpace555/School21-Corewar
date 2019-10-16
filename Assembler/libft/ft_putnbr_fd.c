/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:36:35 by eskeleto          #+#    #+#             */
/*   Updated: 2018/12/06 11:50:00 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_number(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_print_number_fd(int n, int len, int fd)
{
	int	i;
	int	del;

	i = 1;
	del = 1;
	while (i < len)
	{
		del = del * 10;
		i++;
	}
	i = 0;
	while (i < len)
	{
		ft_putchar_fd((n / del) + '0', fd);
		n = n - (n / del) * del;
		del = del / 10;
		i++;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	int	len;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			n = 147483648;
		}
		else
			n = n * (-1);
	}
	if (n == 0)
		ft_putchar_fd('0', fd);
	len = ft_len_number(n);
	ft_print_number_fd(n, len, fd);
}
