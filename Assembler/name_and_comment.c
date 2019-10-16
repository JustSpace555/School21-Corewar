/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_and_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:44:20 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 15:44:23 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_get_all_file(int fd)
{
	char	*allfile;
	int		ret;
	char	buf[BUFF_SIZE + 1];

	allfile = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (allfile != NULL)
			allfile = ft_concat_str(allfile, buf);
		else
			allfile = ft_strdup(buf);
	}
	if (allfile == NULL)
		ft_str_errout("File is empty");
	return (allfile);
}

void	ft_skip_lines_and_spaces(char *allfile, t_asm *assm, int *i)
{
	while (allfile[*i] != '.')
		ft_skip_lines(allfile, assm, i);
	ft_skip_spaces(allfile, i);
}

char	*ft_check_command(char *com, char *allfile, int *i)
{
	char	*temp;
	int		j;

	j = *i;
	if (ft_strlen(allfile) > *i + ft_strlen(com))
		temp = ft_strsub(allfile, *i, ft_strlen(com));
	else
		return (NULL);
	*i = *i + (int)ft_strlen(com);
	if (ft_strequ(temp, com))
	{
		free(temp);
		temp = ft_strsub(allfile, *i, ft_strlen(allfile) - *i);
	}
	else
	{
		*i = j;
		free(temp);
		temp = NULL;
	}
	return (temp);
}

int		ft_find_command(char *allfile, t_asm *assm, int *i, int count)
{
	char	*temp;

	if ((temp = ft_check_command(NAME_CMD_STRING, allfile, i)) != NULL)
	{
		*i = ft_find_name(assm, temp) + *i + 1;
		ft_skip_spaces_and_newline(allfile, assm, i);
		if (count < 2)
			ft_skip_lines_and_spaces(allfile, assm, i);
		return (1);
	}
	else if ((temp = ft_check_command(COMMENT_CMD_STRING, allfile, i)) != NULL)
	{
		*i = ft_find_comment(assm, temp) + *i + 1;
		ft_skip_spaces_and_newline(allfile, assm, i);
		if (count < 2)
			ft_skip_lines_and_spaces(allfile, assm, i);
		return (2);
	}
	else
		ft_free_and_error(assm, allfile,
				"Not valid command of name or comment");
	return (0);
}

void	ft_find_name_and_comment(int fd, t_asm *assm)
{
	char	*allfile;
	int		i;
	int		flag;

	i = 0;
	allfile = ft_get_all_file(fd);
	ft_skip_lines_and_spaces(allfile, assm, &i);
	flag = ft_find_command(allfile, assm, &i, 1);
	if (ft_find_command(allfile, assm, &i, 2) == flag)
		ft_free_and_error(assm, allfile,
				"Not valid command of name or comment");
	assm->newlines = ft_newlines_before_ins(allfile, i);
	free(allfile);
}
