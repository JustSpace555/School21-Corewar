#include "../Headers/virtual_header.h"

void	and_or_xor(t_cursor *cursor, int selector)
{
	unsigned char	dest_reg;
	unsigned char	codage;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if ((codage & 0xC0) == 0 || (codage & 0x30) == 0 || (codage & 0xC) != 4)
	{
		move_cursor(cursor, 4, 1);
		return ;
	}
	dest_reg = 0;
	if ((codage & 0xC0) == 0x40)
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 2), 4, 1);
		if ((codage & 0x30) == 0x10)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 4);
			CHECK_REG(&cursor, dest_reg, 4, 1);
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 3), 4, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] & cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1];
			else if (selector == 1)
				cursor->reg[dest_reg - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] | cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1];
			else
				cursor->reg[dest_reg - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] ^ cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1];
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 7);
			CHECK_REG(&cursor, dest_reg, 4, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] & get_int_data(cursor->cur_pos + 3);
			else if (selector == 1)
				cursor->reg[dest_reg - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] | get_int_data(cursor->cur_pos + 3);
			else
				cursor->reg[dest_reg - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] ^ get_int_data(cursor->cur_pos + 3);
		}
		else if (codage & 0x30)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 5);
			CHECK_REG(&cursor, dest_reg, 4, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] & get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 3) % IDX_MOD);
			else if (selector == 1)
				cursor->reg[dest_reg - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] | get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 3) % IDX_MOD);
			else
				cursor->reg[dest_reg - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] ^ get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 3) % IDX_MOD);
		}
	}
	else if ((codage & 0xC0) == 0x80)
	{
		if ((codage & 0x30) == 0x10)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 7);
			CHECK_REG(&cursor, dest_reg, 4, 1);
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 6), 4, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + 2) & cursor->reg[GET_CUR_POS_BYTE(&cursor, 6) - 1];
			else if (selector == 1)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + 2) | cursor->reg[GET_CUR_POS_BYTE(&cursor, 6) - 1];
			else
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + 2) ^ cursor->reg[GET_CUR_POS_BYTE(&cursor, 6) - 1];
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 10);
			CHECK_REG(&cursor, dest_reg, 4, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + 2) & get_int_data(cursor->cur_pos + 6);
			else if (selector == 1)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + 2) | get_int_data(cursor->cur_pos + 6);
			else
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + 2) ^ get_int_data(cursor->cur_pos + 6);
		}
		else if (codage & 0x30)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 8);
			CHECK_REG(&cursor, dest_reg, 4, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + 2) & get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 6) % IDX_MOD);
			else if (selector == 1)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + 2) | get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 6) % IDX_MOD);
			else
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + 2) ^ get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 6) % IDX_MOD);
		}
	}
	else if ((codage & 0xC0) == 0xC0)
	{
		if ((codage & 0x30) == 0x10)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 5);
			CHECK_REG(&cursor, dest_reg, 4, 1);
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 4), 4, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 2) % IDX_MOD) & cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1];
			else if (selector == 1)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 2) % IDX_MOD) | cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1];
			else
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 2) % IDX_MOD) ^ cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1];
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 8);
			CHECK_REG(&cursor, dest_reg, 4, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 2) % IDX_MOD) & get_int_data(cursor->cur_pos + 4);
			else if (selector == 1)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 2) % IDX_MOD) | get_int_data(cursor->cur_pos + 4);
			else
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 2) % IDX_MOD) ^ get_int_data(cursor->cur_pos + 4);
		}
		else if (codage & 0x30)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 6);
			CHECK_REG(&cursor, dest_reg, 4, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 2) % IDX_MOD) & get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 4) % IDX_MOD);
			else if (selector == 1)
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 2) % IDX_MOD) | get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 4) % IDX_MOD);
			else
				cursor->reg[dest_reg - 1] = get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 2) % IDX_MOD) & get_int_data(cursor->cur_pos + get_short_data(cursor->cur_pos + 4) % IDX_MOD);
		}
	}
	if (cursor->reg[dest_reg - 1] == 0)
		cursor->carry = true;
	else
		cursor->carry = false;
	move_cursor(cursor, 4, 1);
}

void	zjmp(t_cursor *cursor)
{
	if (cursor->carry == false)
		move_cursor(cursor, 2, 0);
	else
		move_cursor(cursor, get_short_data(cursor->cur_pos + 1) % IDX_MOD, 0);
}

void	ldi_lldi(t_cursor *cursor, int selector)
{
	unsigned char	codage;
	unsigned char	dest_reg;

	CHECK_EXEC(&cursor);
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if ((codage & 0xC0) == 0 || (codage & 0x30) > 0x20 || (codage & 0xC) > 4)
	{
		move_cursor(cursor, 2, 1);
		return ;
	}
	if ((codage & 0xC0) == 0x40)
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 2), 2, 1);
		if ((codage & 0x30) == 0x10)
		{
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 3), 2, 1);
			dest_reg = GET_CUR_POS_BYTE(&cursor, 4);
			CHECK_REG(&cursor, dest_reg, 2, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = get_int_data((
					cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] +
					cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1])
					% IDX_MOD);
			else
				cursor->reg[dest_reg - 1] = get_int_data((
					cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] +
					cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1]));
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 5);
			CHECK_REG(&cursor, dest_reg, 2, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = get_int_data((
					cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] +
					get_short_data(cursor->cur_pos + 3)) % IDX_MOD);
			else
				cursor->reg[dest_reg - 1] = get_int_data((
					cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] +
					get_short_data(cursor->cur_pos + 3)));
		}
	}
	else if ((codage & 0xC0) == 0x80)
	{
		if ((codage & 0x30) == 0x10)
		{
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 4), 2, 1);
			dest_reg = GET_CUR_POS_BYTE(&cursor, 5);
			CHECK_REG(&cursor, dest_reg, 2, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = get_int_data((
					get_short_data(cursor->cur_pos + 2) +
					cursor->reg[GET_CUR_POS_BYTE(&cursor, 5) - 1]) % IDX_MOD);
			else
				cursor->reg[dest_reg - 1] = get_int_data((
					get_short_data(cursor->cur_pos + 2) +
					cursor->reg[GET_CUR_POS_BYTE(&cursor, 5) - 1]));
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 6);
			CHECK_REG(&cursor, dest_reg, 2, 1);
			if (selector == 0)
				cursor->reg[dest_reg - 1] = get_int_data((
					get_short_data(cursor->cur_pos + 2) +
					get_short_data(cursor->cur_pos + 4)) % IDX_MOD);
			else
				cursor->reg[dest_reg - 1] = get_int_data((
					get_short_data(cursor->cur_pos + 2) +
					get_short_data(cursor->cur_pos + 4)));
		}
	}
	else if ((codage & 0xC0) == 0xC0)
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 6);
		CHECK_REG(&cursor, dest_reg, 2, 1);
		if (selector == 0)
			cursor->reg[dest_reg - 1] = get_int_data(
				get_short_data(cursor->cur_pos + 2) % IDX_MOD);
		else
			cursor->reg[dest_reg - 1] = get_int_data(
				get_short_data(cursor->cur_pos + 2) % IDX_MOD);
	}
	move_cursor(cursor, 2, 1);
}

unsigned int	get_second_arg(t_cursor *cursor, unsigned char codage, int label_size, short pos)
{
	unsigned int	result;
//	short 			result_short; //посмтреть
	unsigned char	reg_i;

	result = 0;
	pos = pos % MEM_SIZE;
	if ((codage & 0x30) == 48) // 2 arg T_IND
		result = get_short_data(pos) % IDX_MOD;
	else if ((codage & 0x20) == 32)
		result = (label_size == 2) ? get_short_data(pos) : get_int_data(pos);
	else if ((codage & 0x20) == 16)
	{
		reg_i = GET_BYTE(pos);
	/*	CHECK_REG(&cursor, dest_reg, 2, 1);
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 2), 2, 1);
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 3), 2, 1);*/
		result = cursor->reg[reg_i];
	}
//	return ((unsigned int)result_short);
	return (result);
}

void	sti(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned char	src_reg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	src_reg = GET_CUR_POS_BYTE(&cursor, 2);
	/*if ((codage & 0xC0) > 0x40 || (codage & 0x30) == 0 || (codage & 0xC) > 8 ||
		src_reg > REG_NUMBER || src_reg == 0)
	{
		move_cursor(cursor, 2, 1);
		return ;
	}
	if ((codage & 0x30) == 0x10)
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 3), 2, 1);
		if ((codage & 0xC) == 4)
		{
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 4), 2, 1);
			write_amount_of_bytes_data((
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] +
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1]) % IDX_MOD,
				(void *)&cursor->reg[src_reg - 1], 4, cursor->color);
		}
		else if ((codage & 0xC) == 8)
			write_amount_of_bytes_data((
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1] +
				get_short_data(cursor->cur_pos + 4)) % IDX_MOD,
				(void *)&cursor->reg[src_reg - 1], 4, cursor->color);
	}
	else if ((codage & 0x30) == 0x20)
	{
		if ((codage & 0xC) == 4)
		{
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 5), 2, 1);
			write_amount_of_bytes_data((
				get_short_data(cursor->cur_pos + 3) +
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 5) - 1]) % IDX_MOD,
				(void *)&cursor->reg[src_reg - 1], 4, cursor->color);
		}
		else if ((codage & 0xC) == 8)
			write_amount_of_bytes_data((
				get_short_data(cursor->cur_pos + 3) +
				get_short_data(cursor->cur_pos + 5)) % IDX_MOD,
				(void *)&cursor->reg[src_reg - 1], 4, cursor->color);
	}
	else if ((codage & 0x30) == 0x30)
		write_amount_of_bytes_data(
			get_short_data(cursor->cur_pos + 3) % IDX_MOD,
			(void *)&cursor->reg[src_reg - 1], 4, cursor->color);*/
	move_cursor(cursor, 2, 1);
}

void	lld(t_cursor *cursor)
{
	unsigned char	codage;

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
