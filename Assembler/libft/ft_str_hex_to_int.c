/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_hex_to_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:18:22 by eskeleto          #+#    #+#             */
/*   Updated: 2019/07/23 15:18:24 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_hex_to_int(const char *str)
{
	int	i;
	int	num;

	i = 2;
	num = 0;
	while (str[i] != '\0')
	{
		num = num * 16;
		if (str[i] >= '0' && str[i] <= '9')
			num = num + (str[i] - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			num = num + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && str[i] <= 'f')
			num = num + (str[i] - 'a' + 10);
		i++;
	}
	return (num);
}
