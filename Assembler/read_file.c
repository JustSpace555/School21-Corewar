/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:12:52 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 17:12:57 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_empty_line(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] == ' ' || str[i] == '\t'))
			return (0);
		i++;
	}
	return (1);
}

int		ft_comment_line(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] == ' ' || str[i] == '\t'))
		{
			if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

void	ft_delete_comment(char *str)
{
	int	i;

	i = 0;
	while (str[i] != COMMENT_CHAR && str[i] != ALT_COMMENT_CHAR)
		i++;
	str[i] = '\0';
}

char	**ft_get_file(int fd, int count)
{
	char	*line;
	char	**file;
	int		i;

	if (!(file = (char **)malloc(sizeof(char*) * (count + 1))))
		ft_error();
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_empty_line(line) && !ft_comment_line(line))
		{
			if (ft_strchr(line, COMMENT_CHAR)
				|| ft_strchr(line, ALT_COMMENT_CHAR))
			{
				ft_delete_comment(line);
			}
			file[i] = line;
			i++;
		}
		else
			free(line);
	}
	file[i] = NULL;
	return (file);
}

void	ft_counts_line_file(int fd, t_asm *assm)
{
	int		count_lines;
	char	*line;
	char	buf[2];

	line = NULL;
	count_lines = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_empty_line(line) && !ft_comment_line(line))
			count_lines++;
		free(line);
	}
	assm->count_lines = count_lines;
	lseek(fd, -1L, 2);
	if (read(fd, buf, 1) > 0)
	{
		buf[1] = '\0';
		if (buf[0] != '\n')
			ft_str_errout("File must be end on newline");
	}
	else
		ft_str_errout("File must be end on newline!");
}
