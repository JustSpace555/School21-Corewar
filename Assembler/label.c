/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:35:00 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 15:36:59 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_skip_spaces(char *str, int *i)
{
	while (ft_is_space_symb(str[*i]))
		(*i)++;
}

char	*ft_find_label(char *str, t_instr *ins)
{
	int i;
	int start;

	i = 0;
	if (!strchr(str, LABEL_CHAR))
		ins->label = NULL;
	else
	{
		ft_skip_spaces(str, &i);
		start = i;
		while (str[i] != LABEL_CHAR)
		{
			if (!ft_strchr(LABEL_CHARS, str[i]))
			{
				ins->label = NULL;
				return (ft_strdup(str));
			}
			i++;
		}
		ins->label = ft_strsub(str, start, i - start);
		return (ft_strsub(str, i + 1, ft_strlen(str) - i));
	}
	return (ft_strdup(str));
}

int		ft_only_label(char **str, t_instr *ins)
{
	int		i;
	char	*substr;
	char	*temp;

	i = 0;
	temp = ft_strdup(*str);
	ft_skip_spaces(*str, &i);
	free(*str);
	substr = ft_strsub(temp, i, ft_strlen(temp) - i);
	*str = substr;
	free(temp);
	if (*str[0] == '\0')
	{
		if (ins->label != NULL)
		{
			return (1);
		}
		else
			ft_str_errout("Not valid instructions!");
	}
	return (0);
}
