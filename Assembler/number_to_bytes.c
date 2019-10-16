/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_to_bytes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:00:49 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 16:00:50 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_number_to_two_bytes(int fd, int byte)
{
	unsigned int	x;

	if (byte >= 0)
		x = (unsigned int)byte;
	else
	{
		byte = byte * (-1);
		x = (unsigned int)byte;
		x = ~x;
		x++;
	}
	x = ft_reverse_two_byte(x);
	write(fd, &x, 2);
}

void	ft_number_to_bytes(int fd, int byte, t_instr ins)
{
	unsigned int	x;
	t_oper			*oper;
	t_oper			cur_oper;

	if (byte >= 0)
		x = (unsigned int)byte;
	else
	{
		byte = byte * (-1);
		x = (unsigned int)byte;
		x = ~x;
		x++;
	}
	oper = ft_init_oper();
	cur_oper = ft_get_oper(oper, ins);
	if (cur_oper.size_t_dir == 4)
	{
		x = ft_reverse_four_byte(x);
		write(fd, &x, 4);
	}
	else
	{
		x = ft_reverse_two_byte(x);
		write(fd, &x, 2);
	}
}
