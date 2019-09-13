#include "../Headers/virtual_header.h"

void	live(t_cursor *cursor)
{
	CHECK_EXEC(&cursor);
	if (cursor->id == -((int)g_battlefield[cursor->cur_pos + 1].code))
	{
		cursor->is_alive = true;
		g_battlefield[cursor->cur_pos].cursor = false;
		cursor->cur_pos += 2;
		g_battlefield[cursor->cur_pos].cursor = true;
	}
	else
		cursor->is_alive = false;
}

void	st(t_cursor *cursor)
{
	unsigned char	src_reg;
	unsigned char	dest_reg;
	unsigned short	temp;

	CHECK_EXEC(&cursor);
	src_reg = GET_CUR_POS_BYTE(&cursor, 2);
	if (src_reg > REG_NUMBER || !((GET_CUR_POS_BYTE(&cursor, 1) >= 80
			&& GET_CUR_POS_BYTE(&cursor, 1) <= 95)
			|| (GET_CUR_POS_BYTE(&cursor, 1) >= 112
			&& GET_CUR_POS_BYTE(&cursor, 1) <= 127)))
	{
		move_cursor(cursor, 4, 1);
		return ;
	}
	if ((GET_CUR_POS_BYTE(&cursor, 1) & 0x30) == 48)
	{
		temp = get_short_data(cursor->cur_pos + 2);
		g_battlefield[cursor->cur_pos + temp & IDX_MOD].code =
			cursor->reg[src_reg - 1];
	}
	else if ((GET_CUR_POS_BYTE(&cursor, 1) & 0x10) == 16)
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 1);
		CHECK_REG(&cursor, dest_reg, 4, 1);
		cursor->reg[dest_reg - 1] = cursor->reg[src_reg - 1];
	}
	move_cursor(cursor, 4, 1);
}

void	sub(t_cursor *cursor)
{
	unsigned char	dest_reg;
	unsigned char	src_reg_1;
	unsigned char	src_reg_2;

	CHECK_EXEC(&cursor);
	if (!(GET_CUR_POS_BYTE(&cursor, 1) >= 84 &&
		GET_CUR_POS_BYTE(&cursor, 1) <= 87))
	{
		move_cursor(cursor, 4, 1);
		return ;
	}
	src_reg_1 = GET_CUR_POS_BYTE(&cursor, 2);
	src_reg_2 = GET_CUR_POS_BYTE(&cursor, 3);
	dest_reg = GET_CUR_POS_BYTE(&cursor, 4);
	CHECK_REG(&cursor, src_reg_1, 4, 1);
	CHECK_REG(&cursor, src_reg_2, 4, 1);
	CHECK_REG(&cursor, dest_reg, 4, 1);
	cursor->reg[dest_reg - 1] = cursor->reg[src_reg_1 - 1] -
		cursor->reg[src_reg_2 - 1];
	if (cursor->reg[dest_reg - 1] == 0)
		cursor->carry = true;
	else
		cursor->carry = false;
	move_cursor(cursor, 4, 1);
}

void	or(t_cursor *cursor)
{
	unsigned char	dest_src;
	unsigned char	codage;

	CHECK_EXEC(&cursor);
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!((codage >= 84 && codage <= 87) || (codage >= 164 && codage <= 167)
		|| (codage >= 244 && codage <= 247)))
	{
		move_cursor(cursor, 4, 1);
		return ;
	}
	if (codage >= 84 && codage <= 87)
	{
		dest_src = GET_CUR_POS_BYTE(&cursor, 4);
		if (dest_src > REG_NUMBER || GET_CUR_POS_BYTE(&cursor, 2) > REG_NUMBER
			|| GET_CUR_POS_BYTE(&cursor, 3) > REG_NUMBER)
		{
			move_cursor(cursor, 4, 1);
			return ;
		}
		cursor->reg[dest_src - 1] =
			cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] |
			cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1];
	}
	else if (codage >= 164 && codage <= 167)
	{
		dest_src = GET_CUR_POS_BYTE(&cursor, 10);
		CHECK_REG(&cursor, dest_src, 4, 1);
		cursor->reg[dest_src - 1] = get_int_data(cursor->cur_pos + 2)
			| get_int_data(cursor->cur_pos + 6);
	}
	else if (codage >= 244 && codage <= 247)
	{
		dest_src = GET_CUR_POS_BYTE(&cursor, 6);
		CHECK_REG(&cursor, dest_src, 4, 1);
		cursor->reg[dest_src - 1] = get_int_data(
			get_short_data(cursor->cur_pos + 2))
			| get_int_data(get_short_data(cursor->cur_pos + 4));
	}
	move_cursor(cursor, 4, 1);
}

void	zjmp(t_cursor *cursor)
{
	CHECK_EXEC(&cursor);
	if (cursor->carry == false)
	{
		move_cursor(cursor, 2, 0);
		return ;
	}
	move_cursor(cursor, get_short_data(cursor->cur_pos + 1) % IDX_MOD, 0);
}

void	ldi_lldi(t_cursor *cursor, int lever)
{
	unsigned char	codage;
	unsigned char	dest_reg;
	unsigned int	where;

	if (check_for_cycle_exec(cursor) == -1)
		return ;
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!((codage >= 84 && codage <= 87) || (codage >= 164 && codage <= 167)
			|| (codage >= 212 && codage <= 215)
				|| (codage >= 228 && codage <= 231)))
	{
		move_cursor(cursor, 2, 1);
		return ;
	}
	if (codage >= 84 && codage <= 87)
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 4);
		CHECK_REG(&cursor, dest_reg, 2, 1);
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 2), 2, 1);
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 3), 2, 1);
		where = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] +
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1];
		if (lever)
			cursor->reg[dest_reg - 1] = get_int_data(where % IDX_MOD);
		else
			cursor->reg[dest_reg - 1] = get_int_data(where);
	}
	else if (codage >= 164 && codage <= 167)
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 6);
		CHECK_REG(&cursor, dest_reg, 2, 1);
		where = get_short_data(cursor->cur_pos + 2) +
				get_short_data(cursor->cur_pos + 4);
		if (lever)
			cursor->reg[dest_reg - 1] = get_int_data(where % IDX_MOD);
		else
			cursor->reg[dest_reg - 1] = get_int_data(where);
	}
	else
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 3);
		CHECK_REG(&cursor, dest_reg, 2, 1);
		cursor->reg[dest_reg - 1] = get_int_data(
			get_short_data(cursor->cur_pos + 2) % IDX_MOD);
	}
	move_cursor(cursor, 2, 1);
}

void	sti(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	dest_reg;
	int				value;

	CHECK_EXEC(&cursor);
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	dest_reg = GET_CUR_POS_BYTE(&cursor, 2);
	if (!((codage >= 84 && codage <= 87) || (codage >= 104 && codage <= 107)
		|| (codage >= 116 && codage <= 123)) || dest_reg > REG_NUMBER)
	{
		move_cursor(cursor, 2, 1);
		return ;
	}
	value = cursor->reg[dest_reg - 1];
	if (codage >= 84 && codage <= 87)
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 3), 2, 1);
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 4), 2, 1);
		write_amount_of_bytes_data(
			(cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1] +
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1]) % IDX_MOD,
					&cursor->reg[dest_reg - 1], 4);
	}
	else if (codage >= 104 && codage <= 107)
		write_amount_of_bytes_data((get_short_data(cursor->cur_pos + 2)
			+ get_short_data(cursor->cur_pos + 4)) % IDX_MOD,
				&cursor->reg[dest_reg - 1], 4);
	else
		write_amount_of_bytes_data(get_short_data(cursor->cur_pos + 2)
			% IDX_MOD, &cursor->reg[dest_reg - 1], 4);
	move_cursor(cursor, 2, 1);
}

void	lld(t_cursor *cursor)
{
	unsigned char	codage;

	CHECK_EXEC(&cursor);
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!((codage >= 144 && codage <= 159) || (codage >= 208 && codage <= 223)))
	{
		move_cursor(cursor, 4, 1);
		return ;
	}
	if (codage >= 144 && codage <= 159)
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 6), 4, 1);
		cursor->reg[GET_CUR_POS_BYTE(&cursor, 6) - 1] =
			get_int_data(cursor->cur_pos + 2);
	}
	else
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 4), 4, 1);
		cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1] =
			get_int_data(get_short_data(cursor->cur_pos + 2));
	}
	move_cursor(cursor, 4, 1);
}

void	lfork(t_cursor *cursor)
{
	t_cursor	new;

	CHECK_EXEC(&cursor);
	new = *cursor;
	new.cur_pos = get_short_data(cursor->cur_pos + 1);
	make_one_new_cursor(new);
	move_cursor(cursor, 2, 0);
}

void	aff(t_cursor *cursor)
{
	unsigned char	dest_reg;

	CHECK_EXEC(&cursor);
	dest_reg = GET_CUR_POS_BYTE(&cursor, 1);
	CHECK_REG(&cursor, dest_reg, 4, 0);
	ft_printf("%c", cursor->reg[dest_reg - 1] % 256);
	move_cursor(cursor, 2, 0);
}
