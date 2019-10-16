/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:04:19 by eskeleto          #+#    #+#             */
/*   Updated: 2018/12/06 17:03:57 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static int	ft_lenofstr(char const *s)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (ft_isspace(s[i]) && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		size++;
		i++;
	}
	if (size > 0)
	{
		while (ft_isspace(s[i]) || s[i] == '\0')
		{
			i--;
			size--;
		}
		size++;
	}
	return (size);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	size = ft_lenofstr(s);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	while (ft_isspace(s[i]))
		i++;
	while (j < size)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
