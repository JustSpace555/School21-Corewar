/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:39:34 by eskeleto          #+#    #+#             */
/*   Updated: 2018/12/06 17:22:03 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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

static char	*ft_alloc(int len, int sign)
{
	char	*s;

	if (sign == -1)
	{
		if (!(s = (char *)malloc(sizeof(char) * (len + 2))))
			return (NULL);
	}
	else
	{
		if (!(s = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
	}
	return (s);
}

static int	ft_del(int len)
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
	return (del);
}

static char	*ft_str_number(int n, int len, int sign)
{
	char	*s;
	int		i;
	int		del;
	int		j;

	j = 0;
	if (!(s = ft_alloc(len, sign)))
		return (NULL);
	if (sign == -1)
	{
		s[j] = '-';
		j++;
	}
	del = ft_del(len);
	i = 0;
	while (i < len)
	{
		s[j] = (n / del) + '0';
		n = n - (n / del) * del;
		del = del / 10;
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}

char		*ft_itoa(int n)
{
	int	len;
	int	sign;

	sign = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		sign = -1;
		n = n * (-1);
	}
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_len_number(n);
	return (ft_str_number(n, len, sign));
}
