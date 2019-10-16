/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:47:07 by eskeleto          #+#    #+#             */
/*   Updated: 2019/09/10 13:47:11 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_skip_spaces_and_newline(char *allfile, t_asm *assm, int *i)
{
	ft_skip_spaces(allfile, i);
	if (allfile[*i] == '\n')
		(*i)++;
	else if (allfile[*i] == COMMENT_CHAR || allfile[*i] == ALT_COMMENT_CHAR)
	{
		while (allfile[*i] != '\n' && allfile[*i] != '\0')
			(*i)++;
	}
	else
	{
		free(allfile);
		ft_free_asm(assm);
		ft_str_errout("Not valid command");
	}
}

int		ft_comment(t_asm *assm, char *name, int i)
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
			if (ft_strlen(temp) <= COMMENT_LENGTH)
			{
				ft_strcpy(assm->header.comment, temp);
				free(temp);
			}
			else
				ft_free_and_error(assm, temp, "Too long comment");
			return (i);
		}
		i++;
	}
	ft_free_and_error(assm, name, "Not valid command of comment");
	return (i);
}

int		ft_find_comment(t_asm *assm, char *name)
{
	int		i;

	i = 0;
	ft_skip_spaces(name, &i);
	if (name[i] == '\"')
	{
		return (ft_comment(assm, name, i));
	}
	else
	{
		free(name);
		ft_free_asm(assm);
		ft_str_errout("Not valid command of comment");
	}
	return (i);
}
