/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:51:27 by eskeleto          #+#    #+#             */
/*   Updated: 2018/12/06 16:05:14 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*need;

	str = (char *)haystack;
	need = (char *)needle;
	i = 0;
	if (need[i] == '\0')
		return (&str[i]);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while (need[j] == str[i + j] && (i + j) < len)
		{
			if (need[j + 1] == '\0')
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}
