#include "../Headers/virtual_header.h"

void	and(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	offset;
	int				first_arg;
	int				second_arg;
	int				third_arg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!((codage & 0xC0) == 0 || (codage & 0x30) == 0 || (codage & 0xC) != 4))
	{
		offset = 2;
		first_arg = get_first_arg(cursor, codage, 4, &offset);
		second_arg = get_second_arg(cursor, codage, 4, &offset);
		third_arg = get_third_arg(cursor, codage, 4, &offset);
		if (check_reg(third_arg)
			&& check_reg_write_arg(cursor, codage, &first_arg, 1)
			&& check_reg_write_arg(cursor, codage, &second_arg, 2))
		{
			cursor->reg[third_arg - 1] = (first_arg & second_arg);
			if (g_vm->ver == 1)
				ft_printf("P %4d | and %d %d r%d\n", cursor->cursror_id,
										first_arg, second_arg, third_arg);
			cursor->carry = (cursor->reg[third_arg - 1] == 0) ? true : false;
		}
	}
	move_cursor(cursor, 4, codage, 3);
}

void	or(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	offset;
	int				first_arg;
	int				second_arg;
	int				third_arg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!((codage & 0xC0) == 0 || (codage & 0x30) == 0 || (codage & 0xC) != 4))
	{
		offset = 2;
		first_arg = get_first_arg(cursor, codage, 4, &offset);
		second_arg = get_second_arg(cursor, codage, 4, &offset);
		third_arg = get_third_arg(cursor, codage, 4, &offset);
		if (check_reg(third_arg)
			&& check_reg_write_arg(cursor, codage, &first_arg, 1)
			&& check_reg_write_arg(cursor, codage, &second_arg, 2))
		{
			cursor->reg[third_arg - 1] = (first_arg | second_arg);
			if (g_vm->ver == 1)
				ft_printf("P %4d | and %d %d r%d\n", cursor->cursror_id,
										first_arg, second_arg, third_arg);
			cursor->carry = (cursor->reg[third_arg - 1] == 0) ? true : false;
		}
	}
	move_cursor(cursor, 4, codage, 3);
}

void	xor(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	offset;
	int				first_arg;
	int				second_arg;
	int				third_arg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!((codage & 0xC0) == 0 || (codage & 0x30) == 0 || (codage & 0xC) != 4))
	{
		offset = 2;
		first_arg = get_first_arg(cursor, codage, 4, &offset);
		second_arg = get_second_arg(cursor, codage, 4, &offset);
		third_arg = get_third_arg(cursor, codage, 4, &offset);
		if (check_reg(third_arg)
			&& check_reg_write_arg(cursor, codage, &first_arg, 1)
			&& check_reg_write_arg(cursor, codage, &second_arg, 2))
		{
			cursor->reg[third_arg - 1] = (first_arg ^ second_arg);
			if (g_vm->ver == 1)
				ft_printf("P %4d | and %d %d r%d\n", cursor->cursror_id,
										first_arg, second_arg, third_arg);
			cursor->carry = (cursor->reg[third_arg - 1] == 0) ? true : false;
		}
	}
	move_cursor(cursor, 4, codage, 3);
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
		ft_printf("P %4d | zjmp %d %s\n", cursor->cursror_id, address + 1,
										(cursor->carry) ? "OK" : "FAILED");
}

void	ldi(t_cursor *cursor)
{
	unsigned char	codage;
	int				f_arg;
	int				s_arg;
	int				t_arg;
	unsigned short	offset;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if (!((codage & 0xC0) == 0 || (codage & 0x30) == 0x30 ||
		(codage & 0x30) == 0 || (codage & 0xC) != 4))
	{
		offset = 2;
		f_arg = get_first_arg(cursor, codage, 2, &offset);
		s_arg = get_second_arg(cursor, codage, 2, &offset);
		t_arg = get_third_arg(cursor, codage, 2, &offset);
		if (check_reg(t_arg)
			&& check_reg_write_arg(cursor, codage, &f_arg, 1)
			&& check_reg_write_arg(cursor, codage, &s_arg, 2))
		{
			if ((codage & 0xC0) == 0xC0)
				s_arg = 0;
			cursor->reg[t_arg - 1] = get_int_data(cursor->cur_pos +
										(f_arg + s_arg) % IDX_MOD);
		}
	}
	move_cursor(cursor, 2, codage, 3);
}
