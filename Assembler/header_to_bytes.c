/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_to_bytes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:26:15 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 15:26:16 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_prog_name_to_bytes(int fd, char *name)
{
	int				i;
	unsigned int	empty_byte;

	i = 0;
	empty_byte = 0x00;
	while (name[i] != '\0')
	{
		write(fd, &name[i], 1);
		i++;
	}
	while (i < PROG_NAME_LENGTH)
	{
		write(fd, &empty_byte, 1);
		i++;
	}
}

void	ft_null_bytes(int fd)
{
	int				i;
	unsigned int	empty_byte;

	i = 0;
	empty_byte = 0x00;
	while (i < 4)
	{
		write(fd, &empty_byte, 1);
		i++;
	}
}

void	ft_exec_code_size_to_bytes(t_asm *assm, int fd)
{
	unsigned int	x;

	x = ft_reverse_four_byte(assm->header.prog_size);
	write(fd, &x, 4);
}

void	ft_comment_to_bytes(int fd, char *comment)
{
	int				i;
	unsigned int	empty_byte;

	i = 0;
	empty_byte = 0x00;
	while (comment[i] != '\0')
	{
		write(fd, &comment[i], 1);
		i++;
	}
	while (i < COMMENT_LENGTH)
	{
		write(fd, &empty_byte, 1);
		i++;
	}
}

void	ft_header_to_bytes(t_asm *assm, int fd)
{
	unsigned int	x;

	x = ft_reverse_four_byte(assm->header.magic);
	write(fd, &x, sizeof(assm->header.magic));
	ft_prog_name_to_bytes(fd, assm->header.prog_name);
	ft_null_bytes(fd);
	ft_exec_code_size_to_bytes(assm, fd);
	ft_comment_to_bytes(fd, assm->header.comment);
	ft_null_bytes(fd);
}
