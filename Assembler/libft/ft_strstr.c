/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:48:28 by eskeleto          #+#    #+#             */
/*   Updated: 2018/12/04 13:19:35 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*str;
	char	*need;

	i = 0;
	str = (char *)haystack;
	need = (char *)needle;
	if (need[i] == '\0')
		return (&str[i]);
	while (str[i] != '\0')
	{
		j = 0;
		while (need[j] == str[i + j])
		{
			if (need[j + 1] == '\0')
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}
