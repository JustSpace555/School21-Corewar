/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:40:57 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 15:40:58 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_str_errout(char *str)
{
	ft_putstr_fd("error: ", 2);
	ft_putendl_fd(str, 2);
	exit(0);
}

void	ft_create_file(char *argv, t_asm *assm)
{
	char	*name_cor;
	char	*name;
	int		fd;

	name = ft_strsub(argv, 0, ft_strlen(argv) - 2);
	name_cor = ft_strjoin(name, ".cor");
	free(name);
	if ((fd = open(name_cor,
		O_CREAT | O_TRUNC | O_RDWR, S_IREAD | S_IWRITE)) < 0)
		ft_str_errout("unable to create file .cor");
	else
	{
		ft_header_to_bytes(assm, fd);
		ft_in_bytes(assm, fd);
		if (close(fd) == -1)
			ft_str_errout("unable to close file .cor");
	}
	ft_putstr("Writing output program to ");
	ft_putendl(name_cor);
	free(name_cor);
}

void	ft_skip_name_and_comment(int fd, t_asm *assm)
{
	int		i;
	char	*line;

	i = 0;
	while (i < assm->newlines)
	{
		if (get_next_line(fd, &line) > 0)
			free(line);
		i++;
	}
}

void	ft_solution(int fd, char *argv)
{
	t_asm	assm;
	t_oper	*oper;

	oper = ft_init_oper();
	ft_init_asm(&assm);
	ft_find_name_and_comment(fd, &assm);
	lseek(fd, 0L, 0);
	ft_skip_name_and_comment(fd, &assm);
	ft_counts_line_file(fd, &assm);
	if (assm.count_lines == 0)
		ft_str_errout("File don't contains exec code");
	lseek(fd, 0L, 0);
	ft_skip_name_and_comment(fd, &assm);
	assm.file = ft_get_file(fd, assm.count_lines);
	ft_check_file(&assm, oper);
	ft_size_instructions(&assm, oper);
	ft_create_file(argv, &assm);
	ft_free_asm(&assm);
}

int		main(int argc, char **argv)
{
	int	fd;
	int len;

	if (argc == 2)
	{
		len = ft_strlen(argv[1]);
		if (!((len > 2) && (argv[1][len - 2] == '.')
			&& (argv[1][len - 1] == 's')))
			ft_str_errout("File must be <file.s>");
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			ft_str_errout("error");
		else
		{
			ft_solution(fd, argv[1]);
			if (close(fd) == -1)
				ft_str_errout("error");
		}
	}
	else if (argc > 2)
		ft_multiple_files(argc, argv);
	else
		ft_str_errout("usage: ./asm [-m] <file.s> [<files.s> ...]");
	return (0);
}
