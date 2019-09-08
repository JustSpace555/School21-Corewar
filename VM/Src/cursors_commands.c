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
		if (dest_reg > 16)
		{
			if_return(cursor, 4, 1);
			return ;
		}
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
	int				skip;

	if (check_for_cycle_exec(cursor) == -1)
		return ;
	if (!((GET_CUR_POS_BYTE(&cursor, 1) >= 84 && GET_CUR_POS_BYTE(&cursor, 1) <= 87)
		|| (GET_CUR_POS_BYTE(&cursor, 1) >= 164 && GET_CUR_POS_BYTE(&cursor, 1) <= 167)
		|| (GET_CUR_POS_BYTE(&cursor, 1) >= 244 && GET_CUR_POS_BYTE(&cursor, 1) <= 247)))
		{
			get_amount_bytes_to_skip(GET_CUR_POS_BYTE(&cursor, 1), 4);
			return ;
		}
	skip = 1;
	if (GET_CUR_POS_BYTE(&cursor, 1) >= 84 && GET_CUR_POS_BYTE(&cursor, 1) <= 87)
	{
		dest_src = GET_CUR_POS_BYTE(&cursor, 4);
		if (dest_src > 16 || cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] > 16
			|| cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1] > 16)
		{
			get_amount_bytes_to_skip(GET_CUR_POS_BYTE(&cursor, 1), 4);
			return ;
		}
		cursor->reg[dest_src - 1] = cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1]
			| cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1];
		skip += 3;
	}
	else if (GET_CUR_POS_BYTE(&cursor, 1) >= 164 && GET_CUR_POS_BYTE(&cursor, 1) <= 167)
	{
		dest_src = GET_CUR_POS_BYTE(&cursor, 10);
		if (dest_src > 16)
		{
			get_amount_bytes_to_skip(GET_CUR_POS_BYTE(&cursor, 1), 4);
			return ;
		}
		cursor->reg[dest_src - 1] = *(unsigned int *)get_amount_of_bytes_data(
			cursor->cur_pos + 2, 4) | *(unsigned int *)
			get_amount_of_bytes_data(cursor->cur_pos + 6, 4);
		skip += 9;
	}
	else if (GET_CUR_POS_BYTE(&cursor, 1) >= 244 && GET_CUR_POS_BYTE(&cursor, 1) <= 247)
	{
		dest_src = GET_CUR_POS_BYTE(&cursor, 6);
		if (dest_src > 16)
		{
			get_amount_bytes_to_skip(GET_CUR_POS_BYTE(&cursor, 1), 4);
			return ;
		}
		cursor->reg[dest_src - 1] = *(unsigned int *)get_amount_of_bytes_data(
			*(unsigned short *)get_amount_of_bytes_data(cursor->cur_pos + 2,
			 2), 4) | *(unsigned int *)get_amount_of_bytes_data(*(unsigned
			 short *)get_amount_of_bytes_data(cursor->cur_pos + 4, 2), 4);
		skip += 5;
	}
	move_cursor(cursor, 5);
}
