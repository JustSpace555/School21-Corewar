/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 12:29:12 by eskeleto          #+#    #+#             */
/*   Updated: 2018/12/10 16:50:46 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len_number(int n)
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

static void		ft_print_number(int n, int len)
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
		ft_putchar((n / del) + '0');
		n = n - (n / del) * del;
		del = del / 10;
		i++;
	}
}

void			ft_putnbr(int n)
{
	int	len;

	if (n < 0)
	{
		ft_putchar('-');
		if (n == -2147483648)
		{
			ft_putchar('2');
			n = 147483648;
		}
		else
			n = n * (-1);
	}
	if (n == 0)
		ft_putchar('0');
	len = ft_len_number(n);
	ft_print_number(n, len);
}
