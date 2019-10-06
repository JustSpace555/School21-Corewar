#include "../Headers/virtual_header.h"

void	and(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	offset;
	int				first_arg;
	int				second_arg;
	char			third_arg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if ((codage & 0xC0) == 0 || (codage & 0x30) == 0 || (codage & 0xC) != 4)
	{
		move_cursor(cursor, 4, 1, 3);
		return ;
	}
	offset = 2;
	first_arg = (int)get_first_arg(cursor, codage, 4, &offset);
	second_arg = (int)get_second_arg(cursor, codage, 4, &offset);
	third_arg = (int)get_third_arg(cursor, codage, 4, &offset);
	CHECK_REG(&cursor, third_arg, 4, 1, 3);
	if ((codage & 0xC0) == 0x40)
	{
		CHECK_REG(&cursor, first_arg, 4, 1, 3);
		first_arg = cursor->reg[first_arg - 1];
	}
	if ((codage & 0x30) == 0x10)
	{
		CHECK_REG(&cursor, second_arg, 4, 1, 3);
		second_arg = cursor->reg[second_arg - 1];
	}
	cursor->reg[third_arg - 1] = (first_arg & second_arg);
		if (g_vm->ver == 1)
		ft_printf("P %4d | or %d %d r%d\n", cursor->cursror_id, first_arg, second_arg, third_arg);
	if (cursor->reg[third_arg - 1] == 0)
		cursor->carry = true;
	else
		cursor->carry = false;
	move_cursor(cursor, 4, 1, 3);
}

void	or(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	offset;
	int				first_arg;
	int				second_arg;
	char			third_arg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if ((codage & 0xC0) == 0 || (codage & 0x30) == 0 || (codage & 0xC) != 4)
	{
		move_cursor(cursor, 4, 1, 3);
		return ;
	}
	offset = 2;
	first_arg = (int)get_first_arg(cursor, codage, 4, &offset);
	second_arg = (int)get_second_arg(cursor, codage, 4, &offset);
	third_arg = (int)get_third_arg(cursor, codage, 4, &offset);
	CHECK_REG(&cursor, third_arg, 4, 1, 3);
	if ((codage & 0xC0) == 0x40)
	{
		CHECK_REG(&cursor, first_arg, 4, 1, 3);
		first_arg = cursor->reg[first_arg - 1];
	}
	if ((codage & 0x30) == 0x10)
	{
		CHECK_REG(&cursor, second_arg, 4, 1, 3);
		second_arg = cursor->reg[second_arg - 1];
	}
	cursor->reg[third_arg - 1] = (first_arg | second_arg);
	if (g_vm->ver == 1)
		ft_printf("P %4d | or %d %d r%d\n", cursor->cursror_id, first_arg, second_arg, third_arg);
	if (cursor->reg[third_arg - 1] == 0)
		cursor->carry = true;
	else
		cursor->carry = false;
	move_cursor(cursor, 4, 1, 3);
}

void	xor(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	offset;
	int				first_arg;
	int				second_arg;
	char			third_arg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if ((codage & 0xC0) == 0 || (codage & 0x30) == 0 || (codage & 0xC) != 4)
	{
		move_cursor(cursor, 4, 1, 3);
		return ;
	}
	offset = 2;
	first_arg = (int)get_first_arg(cursor, codage, 4, &offset);
	second_arg = (int)get_second_arg(cursor, codage, 4, &offset);
	third_arg = (int)get_third_arg(cursor, codage, 4, &offset);
	CHECK_REG(&cursor, third_arg, 4, 1, 3);
	if ((codage & 0xC0) == 0x40)
	{
		CHECK_REG(&cursor, first_arg, 4, 1, 3);
		first_arg = cursor->reg[first_arg - 1];
	}
	if ((codage & 0x30) == 0x10)
	{
		CHECK_REG(&cursor, second_arg, 4, 1, 3);
		second_arg = cursor->reg[second_arg - 1];
	}
	cursor->reg[third_arg - 1] = (first_arg ^ second_arg);
	if (g_vm->ver == 1)
		ft_printf("P %4d | or %d %d r%d\n", cursor->cursror_id, first_arg, second_arg, third_arg);
	if (cursor->reg[third_arg - 1] == 0)
		cursor->carry = true;
	else
		cursor->carry = false;
	move_cursor(cursor, 4, 1, 3);
}

void	zjmp(t_cursor *cursor)
{
	short	address;

	address = get_short_data(cursor->cur_pos + 1) % IDX_MOD - 1;
	if (cursor->carry == false)
		move_cursor(cursor, 2, 0, 1);
	else
		move_cursor(cursor, address, 0, 1);
	if (g_vm->ver == 1)
		ft_printf("P %4d | zjmp %d %s\n", cursor->cursror_id, address + 1, (cursor->carry) ? "OK" : "FAILED"); // ес че переписать move
}

/*154	ldi(t_cursor *cursor, int selector, t_vm *vm)
{
	unsigned char	codage;
	unsigned short	offset;
	int				f_arg;
	int				s_arg;
	int				t_arg;

	offset = 2;
	f_arg = get_first_arg(cursor, codage, 2, &offset);
	s_arg = get_second_arg(cursor, codage, 2, &offset);
	t_arg = get_third_arg(cursor, codage, 2, &offset);
	if ((codage & 0xC0) == 0x40)
	{
		if (f_arg <= REG_NUMBER && f_arg > 0)
			f_arg =	cursor->reg[f_arg - 1]; 
		else
			return ;	
	}
	if ((codage & 0x30) == 0x10)
	{
		if (f_arg <= REG_NUMBER && f_arg > 0)
			f_arg =	cursor->reg[f_arg - 1]; 
		else
			return ;	
	}

}*/

//void	ldi_lldi(t_cursor *cursor, int selector, t_vm *vm)
void	ldi(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned char	dest_reg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if ((codage & 0xC0) == 0 || (codage & 0x30) > 0x20 || (codage & 0xC) > 4)
	{
		move_cursor(cursor, 2, 1, 3);
		return ;
	}
	if ((codage & 0xC0) == 0x40)
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 2), 2, 1, 3);
		if ((codage & 0x30) == 0x10)
		{
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 3), 2, 1, 3);
			dest_reg = GET_CUR_POS_BYTE(&cursor, 4);
			CHECK_REG(&cursor, dest_reg, 2, 1, 3);
			cursor->reg[dest_reg - 1] = get_int_data((cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] +
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1])
				% IDX_MOD);
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 5);
			CHECK_REG(&cursor, dest_reg, 2, 1, 3);
			cursor->reg[dest_reg - 1] = get_int_data((
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] +
				get_short_data(cursor->cur_pos + 3)) % IDX_MOD);
		}
	}
	else if ((codage & 0xC0) == 0x80)
	{
		if ((codage & 0x30) == 0x10)
		{
			CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 4), 2, 1, 3);
			dest_reg = GET_CUR_POS_BYTE(&cursor, 5);
			CHECK_REG(&cursor, dest_reg, 2, 1, 3);
			cursor->reg[dest_reg - 1] = get_int_data((
				get_short_data(cursor->cur_pos + 2) +
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 5) - 1]) % IDX_MOD);
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 6);
			CHECK_REG(&cursor, dest_reg, 2, 1, 3);
			cursor->reg[dest_reg - 1] = get_int_data((
				get_short_data(cursor->cur_pos + 2) +
				get_short_data(cursor->cur_pos + 4)) % IDX_MOD);
		}
	}
	else if ((codage & 0xC0) == 0xC0)
	{
		dest_reg = GET_CUR_POS_BYTE(&cursor, 6);
		CHECK_REG(&cursor, dest_reg, 2, 1, 3);
		cursor->reg[dest_reg - 1] = get_int_data(
			get_short_data(cursor->cur_pos + 2) % IDX_MOD);
	}
	move_cursor(cursor, 2, 1, 3);
}
