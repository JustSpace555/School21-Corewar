#include "../Headers/virtual_header.h"

void	live(t_cursor *cursor)
{
	CHECK_EXEC(&cursor);
	if (cursor->id == -get_int_data(cursor->cur_pos + 1))
		cursor->is_alive = true;
	else
		cursor->is_alive = false;
	move_cursor(cursor, 4, 0);
}

void	ld(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned char	dest_reg;
	unsigned int	num;

	CHECK_EXEC(&cursor);
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!((codage >= 144 && codage <= 159) || (codage >= 208 && codage <= 223)))
	{
		move_cursor(cursor, 4, 1);
		return ;
	}
	if (codage >= 144 && codage <= 159)
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 6);
		CHECK_REG(&cursor, dest_reg, 4, 1);
		num = get_int_data(cursor->cur_pos + 2);
	}
	else
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 4);
		CHECK_REG(&cursor, dest_reg, 4, 1);
		num = get_int_data(get_short_data(cursor->cur_pos + 2));
	}
	if (num == 0)
		cursor->carry = true;
	else
		cursor->carry = false;
	cursor->reg[dest_reg - 1] = num;
	move_cursor(cursor, 4, 1);
}

void	st(t_cursor *cursor)
{
	unsigned char	src_reg;
	unsigned char	dest_reg;
	short			temp;

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

void	add(t_cursor *cursor)
{
	unsigned char	src_reg_1;
	unsigned char	src_reg_2;
	unsigned char	dest_reg;
	unsigned int	sum;

	CHECK_EXEC(&cursor);
	if (!(GET_CUR_POS_BYTE(&cursor, 1) >= 84 && GET_CUR_POS_BYTE(&cursor, 1) <= 87))
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
	sum = cursor->reg[src_reg_1 - 1] + cursor->reg[src_reg_2 - 1];
	if (sum == 0)
		cursor->carry = true;
	else
		cursor->carry = false;
	cursor->reg[dest_reg - 1] = sum;
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
