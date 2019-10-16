/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:14:17 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 15:14:20 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_arg_is_reg(char *str)
{
	int i;

	if (str[0] == 'r' && (str[1] != '\0' && ft_isdigit(str[1])))
	{
		if (str[2] == '\0')
			return (1);
		if (str[2] != '\0')
		{
			if (ft_isdigit(str[2]))
				i = 3;
			else
				i = 2;
			ft_skip_spaces(str, &i);
			if (str[i] == '\0')
				return (1);
			if (str[i] == SEPARATOR_CHAR)
			{
				ft_skip_spaces(str, &i);
				if (str[i] != '\0')
					return (1);
			}
		}
	}
	return (0);
}

int		ft_arg_is_ind(char *str)
{
	int i;

	if (str[0] == LABEL_CHAR && (str[1] != '\0' && !ft_is_space_symb(str[1])))
		return (1);
	else if (str[0] == '-' || ft_isdigit(str[0]))
	{
		i = 1;
		while (ft_isdigit(str[i]))
			i++;
		ft_skip_spaces(str, &i);
		if (str[i] == '\0')
			return (1);
		if (str[i] == SEPARATOR_CHAR)
		{
			ft_skip_spaces(str, &i);
			if (str[i] != '\0')
				return (1);
		}
	}
	return (0);
}

int		ft_arg_is_dir(char *str)
{
	int i;

	if (str[0] == DIRECT_CHAR && str[1] != '\0')
	{
		if (str[1] == LABEL_CHAR && (str[2] != '\0'
			&& !ft_is_space_symb(str[2])))
			return (1);
		else if (str[1] == '-' || ft_isdigit(str[1]))
		{
			i = 2;
			while (ft_isdigit(str[i]))
				i++;
			ft_skip_spaces(str, &i);
			if (str[i] == '\0')
				return (1);
			if (str[i] == SEPARATOR_CHAR)
			{
				ft_skip_spaces(str, &i);
				if (str[i] != '\0')
					return (1);
			}
		}
	}
	return (0);
}

char	*ft_sub_unnecess(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	ft_skip_spaces(str, &i);
	if (str[i] != '\0')
	{
		if (str[i] == SEPARATOR_CHAR)
			i++;
		ft_skip_spaces(str, &i);
	}
	temp = ft_strsub(str, i, ft_strlen(str) - i);
	free(str);
	return (temp);
}

char	*ft_sub_unnecess_arg3(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	ft_skip_spaces(str, &i);
	temp = ft_strsub(str, i, ft_strlen(str) - i);
	free(str);
	return (temp);
}
