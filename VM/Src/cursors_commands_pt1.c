#include "../Headers/virtual_header.h"

void	live(t_cursor *cursor)
{
	int	i;

	i = 0;
	while (PLAYER(i).identifier != cursor->player_id)
		i++;
	if (get_int_data(cursor->cur_pos + 1) == -PLAYER(i).identifier)
		PLAYER(i).last_alive = CURRENT_CYCLE;
	PLAYER(i).nbr_live++;
	cursor->last_alive = CURRENT_CYCLE;
	g_battlefield[cursor->cur_pos].write_cycles = 100;
	if (g_vm->ver == 1)
		ft_printf("P %4d | live %d\n", cursor->cursror_id, cursor->reg[0]);
	g_amount_live_operations++;
	move_cursor(cursor, 4, 0, 1);
}

void	ld(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned char	dest_reg;
	int				num;
	unsigned short	offset;

	offset = 2;
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if ((codage & 0xC0) == 0 || (codage & 0xC0) == 0x40 || (codage & 0x30) != 0x10)
	{
		move_cursor(cursor, 4, codage, 2);
		return ;
	}
	num = get_first_arg(cursor, codage, 4, &offset);
	dest_reg = get_second_arg(cursor, codage, 4, &offset);
	cursor->carry = (num == 0) ? true : false;
	cursor->reg[dest_reg - 1] = num;
	if (g_vm->ver == 1)
		ft_printf("P %4d | ld %d r%d\n", cursor->cursror_id, num, dest_reg);
	move_cursor(cursor, 4, codage, 2);
}

void	st(t_cursor *cursor) //потестить с типами
{
	unsigned char	src_reg;
	short			temp;
	unsigned char	codage;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	src_reg = GET_CUR_POS_BYTE(&cursor, 2);
	if (!check_reg(src_reg) || (codage & 0xC0) != 0x40 || (codage & 0x30) == 0 || (codage & 0x30) == 0x20)
	{
		move_cursor(cursor, 4, codage, 2);
		return ;
	}
	if ((codage & 0x30) == 48)
	{
		temp = get_short_data(cursor->cur_pos + 3);
		write_amount_of_bytes_data(cursor->cur_pos + temp % IDX_MOD,
								&cursor->reg[src_reg - 1], 4, cursor->color);
		if (g_vm->ver == 1)
			ft_printf("P %4d | st r%d %d\n", cursor->cursror_id, src_reg, temp);
	}
	else if ((codage & 0x10) == 16)
		if (check_reg(GET_CUR_POS_BYTE(&cursor, 3)))
			cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1] = cursor->reg[src_reg - 1];
	move_cursor(cursor, 4, codage, 2);
}

void	add(t_cursor *cursor)
{
	unsigned char	src_reg_1;
	unsigned char	src_reg_2;
	unsigned char	dest_reg;
	unsigned char	codage;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!(codage >= 84 && codage <= 87))
	{
		move_cursor(cursor, 4, codage, 3);
		return ;
	}
	src_reg_1 = GET_CUR_POS_BYTE(&cursor, 2);
	src_reg_2 = GET_CUR_POS_BYTE(&cursor, 3);
	dest_reg = GET_CUR_POS_BYTE(&cursor, 4);
	if (check_reg(src_reg_1) && check_reg(src_reg_2) && check_reg(dest_reg))
	{
		cursor->reg[dest_reg - 1] = cursor->reg[src_reg_1 - 1]
								+ cursor->reg[src_reg_2 - 1];
		if (cursor->reg[dest_reg - 1] == 0)
			cursor->carry = true;
		else
			cursor->carry = false;
		if (g_vm->ver == 1)
			ft_printf("P %4d | add r%d r%d r%d\n",
						cursor->cursror_id, src_reg_1, src_reg_2, dest_reg);
	}
	move_cursor(cursor, 4, codage, 3);
}

void	sub(t_cursor *cursor)
{
	unsigned char	dest_reg;
	unsigned char	src_reg_1;
	unsigned char	src_reg_2;
	unsigned char	codage;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!(codage >= 84 && codage <= 87))
	{
		move_cursor(cursor, 4, codage, 3);
		return ;
	}
	src_reg_1 = GET_CUR_POS_BYTE(&cursor, 2);
	src_reg_2 = GET_CUR_POS_BYTE(&cursor, 3);
	dest_reg = GET_CUR_POS_BYTE(&cursor, 4);
	if (check_reg(src_reg_1) && check_reg(src_reg_2) && check_reg(dest_reg))
	{
		cursor->reg[dest_reg - 1] = cursor->reg[src_reg_1 - 1] -
			cursor->reg[src_reg_2 - 1];
		if (cursor->reg[dest_reg - 1] == 0)
			cursor->carry = true;
		else
			cursor->carry = false;
		if (g_vm->ver == 1)
			ft_printf("P %4d | sub r%d r%d r%d\n",
						cursor->cursror_id, src_reg_1, src_reg_2, dest_reg);
	}
	move_cursor(cursor, 4, codage, 3);
}
