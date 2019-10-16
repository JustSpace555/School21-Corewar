/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursors_commands_pt3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:04:58 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 13:04:59 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

void	sti(t_cursor *cursor)
{
	unsigned char	codage;
	int				src_reg;
	int				second_arg;
	int				third_arg;
	unsigned short	offset;

	offset = 3;
	codage = g_battlefield[cursor->cur_pos + 1].code;
	src_reg = g_battlefield[cursor->cur_pos + 2].code;
	second_arg = 0;
	third_arg = 0;
	if (!((codage & 0xC0) != 0x40 || (codage & 0x30) == 0 ||
		(codage & 0xC) == 0xC || (codage & 0xC) == 0 ||
		src_reg > REG_NUMBER || src_reg == 0))
	{
		second_arg = get_second_arg(cursor, codage, 2, &offset);
		third_arg = get_third_arg(cursor, codage, 2, &offset);
		if (g_vm->ver == 1 || g_vm->ver == 30)
			print_sti(cursor, src_reg, second_arg, third_arg);
		if (check_reg_write_arg(cursor, codage, &second_arg, 2) &&
			check_reg_write_arg(cursor, codage, &third_arg, 3))
			write_int_data(cursor->cur_pos + (second_arg + third_arg) %
						IDX_MOD, cursor->reg[src_reg - 1], cursor->color);
	}
	jump_to_next_op(cursor, codage, 2, 3);
}

void	lld(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	offset;
	int				f_arg;
	int				s_arg;

	codage = g_battlefield[cursor->cur_pos + 1].code;
	if (!((codage & 0xC0) == 0 || (codage & 0xC0) == 0x40 ||
								(codage & 0x30) != 0x10))
	{
		offset = (codage & 0xC0) == 0xC0 ? 4 : 2;
		if ((codage & 0xC0) == 0xC0)
			f_arg = get_int_data(cursor->cur_pos +
					get_short_data(cursor->cur_pos + 2));
		else
			f_arg = get_first_arg(cursor, codage, 4, &offset);
		s_arg = get_second_arg(cursor, codage, 4, &offset);
		if (check_reg(s_arg))
		{
			cursor->reg[s_arg - 1] = f_arg;
			print_lld(cursor, f_arg, s_arg);
			cursor->carry = (cursor->reg[s_arg - 1] == 0) ? true : false;
		}
	}
	jump_to_next_op(cursor, codage, 4, 2);
}

void	lldi(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	offset;
	int				f_arg;
	int				s_arg;
	int				t_arg;

	codage = g_battlefield[cursor->cur_pos + 1].code;
	if (!((codage & 0xC0) == 0 || (codage & 0x30) == 0x30 ||
		(codage & 0x30) == 0 || (codage & 0xC) != 4))
	{
		offset = 2;
		f_arg = get_first_arg(cursor, codage, 2, &offset);
		s_arg = get_second_arg(cursor, codage, 2, &offset);
		t_arg = get_third_arg(cursor, codage, 2, &offset);
		if (check_reg(t_arg) && check_reg_write_arg(cursor, codage, &f_arg, 1)
			&& check_reg_write_arg(cursor, codage, &s_arg, 2))
		{
			cursor->reg[t_arg - 1] = get_int_data(cursor->cur_pos
												+ f_arg + s_arg);
			if (g_vm->ver == 1 || g_vm->ver == 30)
				print_lldi(cursor, f_arg, s_arg, t_arg);
			cursor->carry = (cursor->reg[t_arg - 1] == 0) ? true : false;
		}
	}
	jump_to_next_op(cursor, codage, 2, 3);
}

void	fork_lfork(t_cursor *cursor, int selector)
{
	t_cursor	new;
	short		address;

	new = *cursor;
	address = get_short_data(cursor->cur_pos + 1);
	if ((g_vm->ver == 1 || g_vm->ver == 30) && selector == 0)
		ft_printf("P %4d | fork %d (%d)\n", cursor->cursror_id,
					address, cursor->cur_pos + address % IDX_MOD);
	else if ((g_vm->ver == 1 || g_vm->ver == 30) && selector >= 1)
		ft_printf("P %4d | lfork %d (%d)\n", cursor->cursror_id,
											address, cursor->cur_pos + address);
	if (selector == 0)
		address %= IDX_MOD;
	address = (address < 0) ? MEM_SIZE + address : address;
	new.cur_pos = cursor->cur_pos + address;
	new.cur_pos = (new.cur_pos >= MEM_SIZE) ?
					new.cur_pos % MEM_SIZE : new.cur_pos;
	new.operation_code = '\0';
	cursor->operation_code = '\0';
	print_pc_movement(cursor, 3);
	move_cursor(cursor, 3);
	make_one_new_cursor(new);
}

void	aff(t_cursor *cursor)
{
	unsigned char	dest_reg;
	char			out;
	unsigned char	codage;

	codage = g_battlefield[cursor->cur_pos + 1].code;
	if ((codage & 0xC0) == 0x40)
	{
		dest_reg = g_battlefield[cursor->cur_pos + 2].code;
		if (check_reg(dest_reg))
		{
			out = (char)cursor->reg[dest_reg - 1];
			if (g_vm->aff == 1)
				ft_printf("Aff: %c\n", out);
		}
	}
	print_pc_movement(cursor, 3);
	move_cursor(cursor, 3);
}
