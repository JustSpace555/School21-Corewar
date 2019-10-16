/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mas_strings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:34:57 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/18 12:34:59 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free_mas_strings(char **mas)
{
	int i;

	i = 0;
	while (mas[i] != NULL)
	{
		free(mas[i]);
		mas[i] = NULL;
		i++;
	}
	free(mas);
	return (i);
}
