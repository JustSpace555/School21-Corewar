#include "../Headers/virtual_header.h"

void	live(t_cursor *cursor)
{
	if (check_for_cycle_exec(cursor) == -1)
		return ;
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

void	st(t_cursor	*cursor)
{
	unsigned char	src_reg;
	unsigned char	dest_reg;
	unsigned short	temp;
	int				skip;

	if (check_for_cycle_exec(cursor) == -1)
		return ;
	src_reg = GET_CUR_POS_BYTE(&cursor, 2);
	if (src_reg > 16 || !((GET_CUR_POS_BYTE(&cursor, 1) >= 80
			&& GET_CUR_POS_BYTE(&cursor, 1) <= 95)
			|| (GET_CUR_POS_BYTE(&cursor, 1) >= 112
			&& GET_CUR_POS_BYTE(&cursor, 1) <= 127)))
		{
			if_return(cursor, 4, 1);
			return ;
		}
	skip = 1;
	if ((GET_CUR_POS_BYTE(&cursor, 1) & 0x30) == 48)
	{
		temp = *(unsigned short *)get_amount_of_bytes_data(cursor->cur_pos + 2, 2);
		g_battlefield[cursor->cur_pos + temp & IDX_MOD].code = cursor->reg[src_reg - 1];
		skip += 2;
	}
	else if ((GET_CUR_POS_BYTE(&cursor, 1) & 0x10) == 16)
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 1);
		CHECK_REG(&cursor, dest_reg, 4, 1);
		cursor->reg[dest_reg - 1] = cursor->reg[src_reg - 1];
		skip++;
	}
	move_cursor(cursor, skip);
}

void	sub(t_cursor *cursor)
{
	unsigned char	dest_reg;
	unsigned char	src_reg_1;
	unsigned char	src_reg_2;

	if (check_for_cycle_exec(cursor) == -1)
		return ;
	if (!(GET_CUR_POS_BYTE(&cursor, 1) >= 84 && GET_CUR_POS_BYTE(&cursor, 1) <= 87))
	{
		if_return(cursor, 4, 1);
		return ;
	}
	src_reg_1 = GET_CUR_POS_BYTE(&cursor, 2);
	src_reg_2 = GET_CUR_POS_BYTE(&cursor, 3);
	dest_reg = GET_CUR_POS_BYTE(&cursor, 4);
	if (src_reg_1 > 16 || src_reg_2 > 16 || dest_reg > 16)
	{
		if_return(cursor, 4, 1);
		return ;
	}
	cursor->reg[dest_reg - 1] = cursor->reg[src_reg_1 - 1] - cursor->reg[src_reg_2 - 1];
	if (cursor->reg[dest_reg - 1] == 0)
		cursor->carry = true;
	else
		cursor->carry = false;
	move_cursor(cursor, 4);
}

void	or(t_cursor *cursor)
{
	unsigned char	dest_src;
	unsigned char	codage;
	int				skip;

	if (check_for_cycle_exec(cursor) == -1)
		return ;
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!((codage >= 84 && codage <= 87) || (codage >= 164 && codage <= 167)
		|| (codage >= 244 && codage <= 247)))
		{
			if_return(cursor, 4, 1);
			return ;
		}
	skip = 1;
	if (codage >= 84 && codage <= 87)
	{
		dest_src = GET_CUR_POS_BYTE(&cursor, 4);
		if (dest_src > 16 || GET_CUR_POS_BYTE(&cursor, 2) > 16
			|| GET_CUR_POS_BYTE(&cursor, 3) > 16)
		{
			if_return(cursor, 4, 1);
			return ;
		}
		cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1]
			| cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1];
		skip += 3;
	}
	else if (codage >= 164 && codage <= 167)
	{
		dest_src = GET_CUR_POS_BYTE(&cursor, 10);
		CHECK_REG(&cursor, dest_src, 4, 1);
		cursor->reg[dest_src - 1] = *(unsigned int *)get_amount_of_bytes_data(
			cursor->cur_pos + 2, 4) | *(unsigned int *)
			get_amount_of_bytes_data(cursor->cur_pos + 6, 4);
		skip += 9;
	}
	else if (codage >= 244 && codage <= 247)
	{
		dest_src = GET_CUR_POS_BYTE(&cursor, 6);
		CHECK_REG(&cursor, dest_src, 4, 1);
		cursor->reg[dest_src - 1] = *(unsigned int *)get_amount_of_bytes_data(
			*(unsigned short *)get_amount_of_bytes_data(cursor->cur_pos + 2,
			 2), 4) | *(unsigned int *)get_amount_of_bytes_data(*(unsigned
			 short *)get_amount_of_bytes_data(cursor->cur_pos + 4, 2), 4);
		skip += 5;
	}
	move_cursor(cursor, skip);
}

void	zjmp(t_cursor *cursor)
{
	unsigned short	move;
	if (check_for_cycle_exec(cursor) == -1)
		return ;
	if (cursor->carry == false)
	{
		move_cursor(cursor, 3);
		return ;
	}
	move = *(unsigned short *)get_amount_of_bytes_data(cursor->cur_pos + 1, 2);
	move_cursor(cursor, move % IDX_MOD);
}

void	sti(t_cursor *cursor)
{
	unsigned short	codage;
	unsigned short	dest_reg;
	int				value;
	int				skip;

	if (check_for_cycle_exec(cursor) == -1)
		return ;
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	dest_reg = GET_CUR_POS_BYTE(&cursor, 2);
	if (!((codage >= 84 && codage <= 87) || (codage >= 104 && codage <= 107)
		|| (codage >= 116 && codage <= 123)) || dest_reg > 16)
	{
		if_return(cursor, 2, 1);
		return ;
	}
	value = cursor->reg[dest_reg - 1];
	skip = 1;
	if (codage >= 84 && codage <= 87)
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 3), 2, 1);
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 4), 2, 1);
		write_amount_of_bytes_data((cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1] +
					cursor->reg[GET_CUR_POS_BYTE(&cursor, 4) - 1]) % IDX_MOD, &cursor->reg[dest_reg - 1], 4);
		skip += 3;
	}
	else if (codage >= 104 && codage <= 107)
	{
		write_amount_of_bytes_data((int)(*(unsigned short *)get_amount_of_bytes_data(cursor->cur_pos + 2, 2)
			+ *(unsigned short *)get_amount_of_bytes_data(cursor->cur_pos + 3, 2)) % IDX_MOD, &cursor->reg[dest_reg - 1], 4);
		skip += 5;
	}
	else
	{
		write_amount_of_bytes_data((int)(*(unsigned short *)get_amount_of_bytes_data(cursor->cur_pos + 2, 2)) % IDX_MOD, &cursor->reg[dest_reg - 1], 4);
		if ((codage & 0xF) >= 4 && (codage & 0xF) <= 7)
			skip += 3;
		else
			skip += 4;
	}
	move_cursor(cursor, skip);
}

void	lld(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned char	dest_reg;
	int				skip;

	if (check_for_cycle_exec(cursor) == -1)
		return ;
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!((codage >= 144 && codage <= 159) || (codage >= 208 && codage <= 223)))
	{
		if_return(cursor, 4, 1);
		return ;
	}
	skip = 1;
	if (codage >= 144 && codage <= 159)
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 5);
		CHECK_REG(&cursor, dest_reg, 4, 1);
		cursor->reg[dest_reg - 1] = *(unsigned int *)get_amount_of_bytes_data(cursor->cur_pos + 2, 4);
		skip += 5;
	}
	else
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 3);
		CHECK_REG(&cursor, dest_reg, 4, 1);
		cursor->reg[dest_reg - 1] = *(unsigned int *)get_amount_of_bytes_data(*(unsigned short *)get_amount_of_bytes_data(cursor->cur_pos + 2, 2), 4);
		skip += 3;
	}
	move_cursor(cursor, skip);
}

void	lfork(t_cursor *cursor)
{
	t_cursor	new;

	if (check_for_cycle_exec(cursor) == -1)
		return ;
	new = *cursor;
	new.cur_pos = (int)*(unsigned int *)get_amount_of_bytes_data(cursor->cur_pos + 1, 4);
	make_one_new_cursor(new);
	move_cursor(cursor, 4);
}
