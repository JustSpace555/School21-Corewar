/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:29:14 by eskeleto          #+#    #+#             */
/*   Updated: 2018/12/10 16:47:23 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	unsigned char	*dest;
	size_t			i;

	i = 0;
	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (source < dest)
	{
		while (i < len)
		{
			*(dest + (len - i - 1)) = *(source + (len - i - 1));
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			*(dest + i) = *(source + i);
			i++;
		}
	}
	return (dst);
}
