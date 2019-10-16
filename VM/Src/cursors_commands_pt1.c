/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursors_commands_pt1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:04:52 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 13:04:53 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

void	live(t_cursor *cursor)
{
	int	i;
	int	arg;

	i = 0;
	while (g_players[i].identifier != cursor->player_id)
		i++;
	arg = get_int_data(cursor->cur_pos + 1);
	g_players[i].nbr_live++;
	cursor->last_alive = CURRENT_CYCLE;
	g_battlefield[cursor->cur_pos].write_cycles = 100;
	if (g_vm->ver == 1 || g_vm->ver == 30)
		ft_printf("P%5d | live %d\n", cursor->cursror_id, arg);
	if (arg <= -1 && arg >= -g_vm->amount_players)
	{
		g_vm->last_live_player = ft_abs(arg);
		g_players[i].last_alive = CURRENT_CYCLE;
		if (g_vm->ver == 3)
			ft_printf("Player %d (%s) is said to be alive\n",
			(arg < 0) ? -arg : arg, \
			g_players[(arg < 0) ? -arg - 1 : arg - 1].name);
	}
	g_amount_live_operations++;
	print_pc_movement(cursor, 5);
	move_cursor(cursor, 5);
}

void	ld(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned char	dest_reg;
	int				num;
	unsigned short	offset;

	offset = 2;
	codage = g_battlefield[cursor->cur_pos + 1].code;
	if ((codage & 0xC0) == 0 || (codage & 0xC0) == 0x40
							|| (codage & 0x30) != 0x10)
	{
		jump_to_next_op(cursor, codage, 4, 2);
		return ;
	}
	num = get_first_arg(cursor, codage, 4, &offset);
	dest_reg = get_second_arg(cursor, codage, 4, &offset);
	if (check_reg(dest_reg))
	{
		cursor->carry = (num == 0) ? true : false;
		cursor->reg[dest_reg - 1] = num;
		if (g_vm->ver == 1 || g_vm->ver == 30)
			ft_printf("P %4d | ld %d r%d\n", cursor->cursror_id,
											num, dest_reg);
	}
	jump_to_next_op(cursor, codage, 4, 2);
}

void	st(t_cursor *cursor)
{
	unsigned char	src_reg;
	short			temp;
	unsigned char	codage;

	codage = g_battlefield[cursor->cur_pos + 1].code;
	src_reg = g_battlefield[cursor->cur_pos + 2].code;
	if (check_reg(src_reg) && (codage & 0xC0) == 0x40 &&
		(codage & 0x30) != 0 && (codage & 0x30) != 0x20)
	{
		if ((codage & 0x30) == 48)
		{
			temp = get_short_data(cursor->cur_pos + 3);
			write_int_data(cursor->cur_pos + temp % IDX_MOD,
					cursor->reg[src_reg - 1], cursor->color);
			print_st(cursor, src_reg, temp);
		}
		else if ((codage & 0x10) == 16 &&
			check_reg(g_battlefield[cursor->cur_pos + 3].code))
		{
			cursor->reg[g_battlefield[cursor->cur_pos + 3].code - 1] =
									cursor->reg[src_reg - 1];
			print_st(cursor, src_reg, g_battlefield[cursor->cur_pos + 3].code);
		}
	}
	jump_to_next_op(cursor, codage, 4, 2);
}

void	add(t_cursor *cursor)
{
	unsigned char	src_reg_1;
	unsigned char	src_reg_2;
	unsigned char	dest_reg;
	unsigned char	codage;

	codage = g_battlefield[cursor->cur_pos + 1].code;
	if (!(codage >= 84 && codage <= 87))
	{
		jump_to_next_op(cursor, codage, 4, 3);
		return ;
	}
	src_reg_1 = g_battlefield[cursor->cur_pos + 2].code;
	src_reg_2 = g_battlefield[cursor->cur_pos + 3].code;
	dest_reg = g_battlefield[cursor->cur_pos + 4].code;
	if (check_reg(src_reg_1) && check_reg(src_reg_2) && check_reg(dest_reg))
	{
		cursor->reg[dest_reg - 1] = cursor->reg[src_reg_1 - 1]
								+ cursor->reg[src_reg_2 - 1];
		cursor->carry = (cursor->reg[dest_reg - 1] == 0) ? true : false;
		if (g_vm->ver == 1 || g_vm->ver == 30)
			ft_printf("P %4d | add r%d r%d r%d\n",
						cursor->cursror_id, src_reg_1, src_reg_2, dest_reg);
	}
	jump_to_next_op(cursor, codage, 4, 3);
}

void	sub(t_cursor *cursor)
{
	unsigned char	dest_reg;
	unsigned char	src_reg_1;
	unsigned char	src_reg_2;
	unsigned char	codage;

	codage = g_battlefield[cursor->cur_pos + 1].code;
	if (!(codage >= 84 && codage <= 87))
	{
		jump_to_next_op(cursor, codage, 4, 3);
		return ;
	}
	src_reg_1 = g_battlefield[cursor->cur_pos + 2].code;
	src_reg_2 = g_battlefield[cursor->cur_pos + 3].code;
	dest_reg = g_battlefield[cursor->cur_pos + 4].code;
	if (check_reg(src_reg_1) && check_reg(src_reg_2) && check_reg(dest_reg))
	{
		cursor->reg[dest_reg - 1] = cursor->reg[src_reg_1 - 1] -
			cursor->reg[src_reg_2 - 1];
		cursor->carry = (cursor->reg[dest_reg - 1] == 0) ? true : false;
		if (g_vm->ver == 1 || g_vm->ver == 30)
			ft_printf("P %4d | sub r%d r%d r%d\n",
						cursor->cursror_id, src_reg_1, src_reg_2, dest_reg);
	}
	jump_to_next_op(cursor, codage, 4, 3);
}
