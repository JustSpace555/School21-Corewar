/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:53:36 by eskeleto          #+#    #+#             */
/*   Updated: 2018/12/11 12:56:12 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c)
			count++;
		i++;
	}
	if (s[i] == '\0' && s[i - 1] != c)
		count++;
	return (count);
}

static int		ft_len_word(const char *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char		*ft_write_word(const char *s, char c, int *i)
{
	char	*str;
	int		j;

	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_len_word(s, c, *i) + 1));
	if (str == NULL)
		return (NULL);
	while (s[*i] != c && s[*i] != '\0')
	{
		str[j] = s[*i];
		j++;
		*i = *i + 1;
	}
	str[j] = '\0';
	while (s[*i] == c && s[*i] != '\0')
		*i = *i + 1;
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		count;
	char	**str;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	count = ft_count_words(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	while (s[i] == c)
		i++;
	while (j < count)
	{
		if (!(str[j] = ft_write_word(s, c, &i)))
		{
			free(str);
			return (NULL);
		}
		j++;
	}
	str[j] = NULL;
	return (str);
}
