#include "../Headers/virtual_header.h"

void	and_or_xor(t_cursor *cursor, int selector)
{
	unsigned char	dest_src;
	unsigned char	codage;

	CHECK_EXEC(&cursor);
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if ((codage & 0xC0) == 0 || (codage & 0x30) == 0 || (codage & 0xC) != 4)
	{
		move_cursor(cursor, 4, 1);
		return ;
	}
	if ((codage & 0xC0) == 0x40)
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 2), 4, 1);
		if ((codage & 0x30) == 0x10)
		{
			dest_src = GET_CUR_POS_BYTE(&cursor, 4);
			CHECK_REG(&cursor, dest_src, 4, 1);
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 3), 4, 1);
			if (selector == 0)
				cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1] & cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1];
			else if (selector == 1)
				cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1] | cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1];
			else
				cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1] ^ cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1];
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_src = GET_CUR_POS_BYTE(&cursor, 7);
			CHECK_REG(&cursor, dest_src, 4, 1);
			if (selector == 0)
				cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] & get_int_data(cursor->cur_pos + 3);
			else if (selector == 1)
				cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] | get_int_data(cursor->cur_pos + 3);
			else
				cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] ^ get_int_data(cursor->cur_pos + 3);
		}
		else if ((codage & 0x30) == 0x30)
		{
			dest_src = GET_CUR_POS_BYTE(&cursor, 5);
			CHECK_REG(&cursor, dest_src, 4, 1);
			if (selector == 0)
				cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] & get_int_data(get_short_data(cursor->cur_pos + 3) % IDX_MOD);
			else if (selector == 1)
				cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] | get_int_data(get_short_data(cursor->cur_pos + 3) % IDX_MOD);
			else
				cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] ^ get_int_data(get_short_data(cursor->cur_pos + 3) % IDX_MOD);
		}
	}
	else if ((codage & 0xC0) == 0x80)
	{
		if ((codage & 0x30) == 0x10)
		{
			dest_src = GET_CUR_POS_BYTE(&cursor, 7);
			CHECK_REG(&cursor, dest_src, 4, 1);
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 6), 4, 1);
			if (selector == 0)
				cursor->reg[dest_src - 1] = get_int_data(cursor->cur_pos + 2) & cursor->reg[GET_CUR_POS_BYTE(&cursor, 6) - 1];
			else if (selector == 1)
				cursor->reg[dest_src - 1] = get_int_data(cursor->cur_pos + 2) | cursor->reg[GET_CUR_POS_BYTE(&cursor, 6) - 1];
			else
				cursor->reg[dest_src - 1] = get_int_data(cursor->cur_pos + 2) ^ cursor->reg[GET_CUR_POS_BYTE(&cursor, 6) - 1];
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_src = GET_CUR_POS_BYTE(&cursor, 11);
			CHECK_REG(&cursor, dest_src, 4, 1);
			if (selector == 0)
				cursor->reg[dest_src - 1] = get_int_data(cursor->cur_pos + 2) & get_int_data(cursor->cur_pos + 6);
			else if (selector == 1)
				cursor->reg[dest_src - 1] = get_int_data(cursor->cur_pos + 2) | get_int_data(cursor->cur_pos + 6);
			else
				cursor->reg[dest_src - 1] = get_int_data(cursor->cur_pos + 2) ^ get_int_data(cursor->cur_pos + 6);
		}
		else if ((codage & 0x30) == 0x30)
		{
			dest_src = GET_CUR_POS_BYTE(&cursor, 8);
			CHECK_REG(&cursor, dest_src, 4, 1);
			if (selector == 0)
				cursor->reg[dest_src - 1] = get_int_data(cursor->cur_pos + 2) & get_int_data(get_short_data(cursor->cur_pos + 6) % IDX_MOD);
			else if (selector == 1)
				cursor->reg[dest_src - 1] = get_int_data(cursor->cur_pos + 2) | get_int_data(get_short_data(cursor->cur_pos + 6) % IDX_MOD);
			else
				cursor->reg[dest_src - 1] = get_int_data(cursor->cur_pos + 2) ^ get_int_data(get_short_data(cursor->cur_pos + 6) % IDX_MOD);
		}
	}
	else if ((codage & 0xC0) == 0xC0)
	{
		if ((codage & 0x30) == 0x10)
		{
			dest_src = GET_CUR_POS_BYTE(&cursor, 5);
			CHECK_REG(&cursor, dest_src, 4, 1);
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 4), 4, 1);
			if (selector == 0)
				cursor->reg[dest_src - 1] = get_int_data(get_short_data(cursor->cur_pos + 2) % IDX_MOD) & cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1];
			else if (selector == 1)
				cursor->reg[dest_src - 1] = get_int_data(get_short_data(cursor->cur_pos + 2) % IDX_MOD) | cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1];
			else
				cursor->reg[dest_src - 1] = get_int_data(get_short_data(cursor->cur_pos + 2) % IDX_MOD) ^ cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1];
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_src = GET_CUR_POS_BYTE(&cursor, 8);
			CHECK_REG(&cursor, dest_src, 4, 1);
			if (selector == 0)
				cursor->reg[dest_src - 1] = get_int_data(get_short_data(cursor->cur_pos + 2) % IDX_MOD) & get_int_data(cursor->cur_pos + 4);
			else if (selector == 1)
				cursor->reg[dest_src - 1] = get_int_data(get_short_data(cursor->cur_pos + 2) % IDX_MOD) | get_int_data(cursor->cur_pos + 4);
			else
				cursor->reg[dest_src - 1] = get_int_data(get_short_data(cursor->cur_pos + 2) % IDX_MOD) ^ get_int_data(cursor->cur_pos + 4);
		}
		else if ((codage & 0x30) == 0x30)
		{
			dest_src = GET_CUR_POS_BYTE(&cursor, 6);
			CHECK_REG(&cursor, dest_src, 4, 1);
			if (selector == 0)
				cursor->reg[dest_src - 1] = get_int_data(get_short_data(cursor->cur_pos + 2) % IDX_MOD) & get_int_data(get_short_data(cursor->cur_pos + 4) % IDX_MOD);
			else if (selector == 1)
				cursor->reg[dest_src - 1] = get_int_data(get_short_data(cursor->cur_pos + 2) % IDX_MOD) | get_int_data(get_short_data(cursor->cur_pos + 4) % IDX_MOD);
			else
				cursor->reg[dest_src - 1] = get_int_data(get_short_data(cursor->cur_pos + 2) % IDX_MOD) & get_int_data(get_short_data(cursor->cur_pos + 4) % IDX_MOD);
		}
	}
	move_cursor(cursor, 4, 1);
}

void	zjmp(t_cursor *cursor)
{
	CHECK_EXEC(&cursor);
	if (cursor->carry == false)
		move_cursor(cursor, 2, 0);
	else
		move_cursor(cursor, get_short_data(cursor->cur_pos + 1) % IDX_MOD, 0);
}

void	ldi_lldi(t_cursor *cursor, int selector)
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
		if (selector == 0)
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
		if (selector == 0)
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
					&cursor->reg[dest_reg - 1], 4, g_battlefield[cursor->cur_pos].color);
	}
	else if (codage >= 104 && codage <= 107)
		write_amount_of_bytes_data((get_short_data(cursor->cur_pos + 3)
			+ get_short_data(cursor->cur_pos + 5)) % IDX_MOD,
				&cursor->reg[dest_reg - 1], 4, g_battlefield[cursor->cur_pos].color);
	else
		write_amount_of_bytes_data(get_short_data(cursor->cur_pos + 3)
			% IDX_MOD, &cursor->reg[dest_reg - 1], 4, g_battlefield[cursor->cur_pos].color);
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
