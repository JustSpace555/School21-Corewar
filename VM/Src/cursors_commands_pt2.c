#include "../Headers/virtual_header.h"

void	and_or_xor(t_cursor *cursor, int selector, t_vm *vm)
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

void	zjmp(t_cursor *cursor, t_vm *vm)
{
	if (cursor->carry == false)
		move_cursor(cursor, 2, 0);
	else
		move_cursor(cursor, get_short_data(cursor->cur_pos + 1) % IDX_MOD - 1, 0);
	if (vm->ver == 1)
		ft_printf("P %4d | zjmp %d %s\n", cursor->id, get_short_data(cursor->cur_pos + 1) % IDX_MOD, (cursor->carry) ? "OK" : "FAILED");
}

void	ldi_lldi(t_cursor *cursor, int selector, t_vm *vm)
{
	unsigned char	codage;
	unsigned char	dest_reg;

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

unsigned int	get_first_arg(t_cursor *cursor, unsigned char codage, int label_size, unsigned short *offset)
{
	unsigned int	result;
	unsigned char	reg_i;
	short			address;
	unsigned short	pos;

	result = 0;
	pos = (cursor->cur_pos + *offset) % MEM_SIZE;
	if ((codage & 0xC0) == 192) // 2 arg T_IND
	{
		address = get_short_data(pos) % IDX_MOD;
		result =  get_int_data(cursor->cur_pos + address); //проверить с учетом позиции каретки или нет
		*offset += 2;
	}
	else if ((codage & 0x80) == 128)
	{
		result = (label_size == 2) ? get_short_data(pos) : get_int_data(pos);
		*offset += (label_size == 2) ? 2 : 4;
	}
	else if ((codage & 0x40) == 64)
	{
		reg_i = GET_BYTE(pos);
		result = reg_i;
		*offset += 1;
	}
	return (result);
}

unsigned int	get_second_arg(t_cursor *cursor, unsigned char codage, int label_size, unsigned short *offset)
{
	unsigned int	result;
	unsigned char	reg_i;
	short			address;
	unsigned short	pos;

	result = 0;
	pos = (cursor->cur_pos + *offset) % MEM_SIZE;
	if ((codage & 0x30) == 48)
	{
		address = get_short_data(pos) % IDX_MOD;
		result =  get_int_data(cursor->cur_pos + address); //проверить с учетом позиции каретки или нет
		*offset += 2;
	}
	else if ((codage & 0x20) == 32)
	{
		result = (label_size == 2) ? get_short_data(pos) : get_int_data(pos);
		*offset += (label_size == 2) ? 2 : 4;
	}
	else if ((codage & 0x10) == 16) // нет проверки
	{
		reg_i = GET_BYTE(pos);
		result = reg_i;
		*offset += 1;
	}
	return (result);
}

unsigned int	get_third_arg(t_cursor *cursor, unsigned char codage, int label_size, unsigned short *offset)
{
	unsigned int	result;
	unsigned char	reg_i;
	short			address;
	unsigned short	pos;

	result = 0;
	pos = (cursor->cur_pos + *offset) % MEM_SIZE;
	if ((codage & 0xC) == 12) // 2 arg T_IND
	{
		address = get_short_data(pos) % IDX_MOD;
		result =  get_int_data(cursor->cur_pos + address); //проверить с учетом позиции каретки или нет
		*offset += 2;
	}
	else if ((codage & 0x8) == 8)
	{
		result = (label_size == 2) ? get_short_data(pos) : get_int_data(pos);
		*offset += (label_size == 2) ? 2 : 4;
	}
	else if ((codage & 0x4) == 4)
	{
		reg_i = GET_BYTE(pos);
		result = reg_i;
		*offset += 1;
	}
	return (result);
}

void	print_sti(t_cursor *cursor, int reg, int sec_arg, int third_arg)
{
	ft_printf("P %4d | sti r%d %d %d\n", cursor->id, reg, sec_arg, third_arg);
	ft_printf("      | -> store to %d + %d = %d (with pc and mod %d)\n", sec_arg, third_arg, sec_arg + third_arg, cursor->cur_pos + ((sec_arg + third_arg) % IDX_MOD));
}

void	sti(t_cursor *cursor, t_vm *vm)
{
	unsigned char	codage;
	unsigned char	src_reg;
	int				address; // подумать насчет типа
	int				second_arg;
	int				third_arg;
	unsigned short	offset;

	offset = 3;
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	src_reg = GET_CUR_POS_BYTE(&cursor, 2);
	second_arg = 0;
	third_arg = 0;
	if ((codage & 0xC0) > 0x40 || (codage & 0x30) == 0 || (codage & 0xC) > 8 ||
		src_reg > REG_NUMBER || src_reg == 0)
	{
		move_cursor(cursor, 2, 1);
		return ;
	}
	if ((codage & 0x30) == 0x30)
		second_arg = (int)get_second_arg(cursor, codage, 2, &offset);
	else if ((codage & 0x30) == 0x20)
		second_arg = get_second_arg(cursor, codage, 2, &offset);
	else if ((codage & 0x30) == 0x10)
		second_arg = get_second_arg(cursor, codage, 2, &offset);
	if ((codage & 0xC) == 8)
		third_arg = get_third_arg(cursor, codage, 2, &offset);
	else if ((codage & 0xC) == 4)
		third_arg = get_third_arg(cursor, codage, 2, &offset);

	if((codage & 0x30) == 0x10 && (codage & 0xC) == 4)
		address = cursor->cur_pos + ((cursor->reg[second_arg - 1] + cursor->reg[third_arg - 1]) % IDX_MOD);
	else if ((codage & 0x30) != 0x10 && (codage & 0xC) == 4)
		address = cursor->cur_pos + ((second_arg + cursor->reg[third_arg - 1]) % IDX_MOD);
	else if ((codage & 0x30) == 0x10 && (codage & 0xC) != 4)
		address = cursor->cur_pos + ((cursor->reg[second_arg - 1] + third_arg - 1) % IDX_MOD);
	else
		address = cursor->cur_pos + (second_arg + third_arg) % IDX_MOD;
	write_amount_of_bytes_data(address, &cursor->reg[src_reg - 1], 4, cursor->color);
	if (vm->ver == 1)
		print_sti(cursor, src_reg, second_arg, third_arg);
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

void	lld(t_cursor *cursor, t_vm *vm)
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
