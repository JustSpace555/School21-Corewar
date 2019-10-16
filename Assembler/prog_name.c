/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:16:12 by eskeleto          #+#    #+#             */
/*   Updated: 2019/09/10 14:16:13 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_name(t_asm *assm, char *name, int i)
{
	int		start;
	char	*temp;

	i++;
	start = i;
	while (name[i] != '\0')
	{
		if (name[i] == '\"')
		{
			temp = ft_strsub(name, start, i - start);
			free(name);
			if (ft_strlen(temp) <= PROG_NAME_LENGTH)
			{
				ft_strcpy(assm->header.prog_name, temp);
				free(temp);
			}
			else
				ft_free_and_error(assm, temp, "Too long program name");
			return (i);
		}
		i++;
	}
	ft_free_and_error(assm, name, "Not valid command of name");
	return (i);
}

int		ft_find_name(t_asm *assm, char *name)
{
	int		i;

	i = 0;
	ft_skip_spaces(name, &i);
	if (name[i] == '\"')
	{
		return (ft_name(assm, name, i));
	}
	else
		ft_free_and_error(assm, name, "Not valid command of name");
	return (i);
}

int		ft_newlines_before_ins(char *allfile, int i)
{
	int count;
	int j;

	count = 0;
	j = 0;
	while (j <= i)
	{
		if (allfile[j] == '\n')
			count++;
		j++;
	}
	return (count);
}

void	ft_skip_lines(char *allfile, t_asm *assm, int *i)
{
	ft_skip_spaces(allfile, i);
	if (allfile[*i] == '.')
		return ;
	if (allfile[*i] == COMMENT_CHAR)
	{
		while (allfile[*i] != '\n' && allfile[*i] != '\0')
			(*i)++;
	}
	else if (allfile[*i] != '\n')
	{
		free(allfile);
		ft_free_asm(assm);
		ft_str_errout("Not valid command");
	}
	(*i)++;
}
