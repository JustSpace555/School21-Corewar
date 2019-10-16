/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:37:04 by eskeleto          #+#    #+#             */
/*   Updated: 2019/10/16 15:37:06 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_check_symbols(int fd)
{
	int		i;
	char	*line;

	i = 0;
	if (get_next_line(fd, &line) > 0)
	{
		ft_skip_spaces(line, &i);
		while (i < (int)ft_strlen(line))
		{
			if (line[i] != '\0' || line[i] != COMMENT_CHAR
				|| line[i] != ALT_COMMENT_CHAR)
			{
				ft_str_errout("File must be end on newline");
			}
			i++;
		}
	}
}

void	ft_check_str(int fd)
{
	char			buf[2];

	while (read(fd, buf, 1) > 0)
	{
		buf[1] = '\0';
		if (buf[0] != '\n')
			lseek(fd, -1L, 1);
		else
		{
			ft_check_symbols(fd);
		}
	}
}
