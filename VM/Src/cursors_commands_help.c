#include "../Headers/virtual_header.h"

unsigned int	get_first_arg(t_cursor *cursor, unsigned char codage,
								int label_size, unsigned short *offset)
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
		*offset += label_size;
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
		*offset += label_size;
	}
	else if ((codage & 0x10) == 16)
	{
		reg_i = GET_BYTE(pos);
		result = reg_i;
		*offset += 1;
	}
	return (result);
}

unsigned int	get_third_arg(t_cursor *cursor, unsigned char codage,
								int label_size, unsigned short *offset)
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
		*offset += label_size;
	}
	else if ((codage & 0x4) == 4)
	{
		reg_i = GET_BYTE(pos);
		result = reg_i;
		*offset += 1;
	}
	return (result);
}

t_bool			check_reg(unsigned char reg)
{
	return (reg > 16 || reg == 0 ? false : true);
}

int				check_reg_write_arg(t_cursor *cursor, unsigned char codage, int *value)
{
	if ((codage & 0xC0) == 0x40 || (codage & 0x30) == 10 || (codage & 0xC) == 4)
	{
		if (check_reg(*value))
			*value = cursor->reg[(*value) - 1];
		else
			return (0);
	}
	return (1);
}
