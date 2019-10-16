/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:01:54 by eskeleto          #+#    #+#             */
/*   Updated: 2019/09/10 14:01:57 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_multiple_files(int argc, char **argv)
{
	int i;
	int fd;

	i = 2;
	if (ft_strequ(argv[1], "-m"))
	{
		while (i < argc)
		{
			if (!((ft_strlen(argv[i]) > 2)
			&& (argv[i][ft_strlen(argv[i]) - 2] == '.')
			&& (argv[i][ft_strlen(argv[i]) - 1] == 's')))
				ft_str_errout("File must be <file.s>");
			if ((fd = open(argv[i], O_RDONLY)) < 0)
				ft_str_errout("error");
			else
			{
				ft_solution(fd, argv[i]);
				if (close(fd) == -1)
					ft_str_errout("error");
			}
			i++;
		}
	}
	else
		ft_str_errout("usage: ./asm [-m] <file.s> [<files.s> ...]");
}
