/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:06:04 by eskeleto          #+#    #+#             */
/*   Updated: 2018/12/11 12:36:52 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(const char *src, int count)
{
	int	j;

	j = 0;
	while (src[j] != '\0')
	{
		count++;
		j++;
	}
	return (count);
}

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	if (size > i)
	{
		count = i;
		count = ft_len(src, count);
		while (src[j] != '\0' && i < size - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
	}
	else
		return (size + ft_strlen(src));
	return (count);
}
