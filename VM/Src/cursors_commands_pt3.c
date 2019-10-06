#include "../Headers/virtual_header.h"

void	lldi(t_cursor *cursor)
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
			cursor->reg[dest_reg - 1] = get_int_data((
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] +
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 3) - 1]));
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 5);
			CHECK_REG(&cursor, dest_reg, 2, 1, 3);
			cursor->reg[dest_reg - 1] = get_int_data((
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 2) - 1] +
				get_short_data(cursor->cur_pos + 3)));
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
				cursor->reg[GET_CUR_POS_BYTE(&cursor, 5) - 1]));
		}
		else if ((codage & 0x30) == 0x20)
		{
			dest_reg = GET_CUR_POS_BYTE(&cursor, 6);
			CHECK_REG(&cursor, dest_reg, 2, 1, 3);
			cursor->reg[dest_reg - 1] = get_int_data((
				get_short_data(cursor->cur_pos + 2) +
				get_short_data(cursor->cur_pos + 4)));
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

void	sti(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned char	src_reg;
	int				address; // подумать насчет типа
	long int		second_arg;
	long int		third_arg;
	unsigned short	offset;

	offset = 3;
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	src_reg = GET_CUR_POS_BYTE(&cursor, 2);
	second_arg = 0;
	third_arg = 0;
	if ((codage & 0xC0) > 0x40 || (codage & 0x30) == 0 || (codage & 0xC) > 8 ||
		src_reg > REG_NUMBER || src_reg == 0)
	{
		move_cursor(cursor, 2, 1, 3);
		return ;
	}
	/*if ((codage & 0x30) == 0x30)
		second_arg = (long int)get_second_arg(cursor, codage, 2, &offset);
	else if ((codage & 0x30) == 0x20)*/
	second_arg = get_second_arg(cursor, codage, 2, &offset);
	/*else if ((codage & 0x30) == 0x10)
		second_arg = get_second_arg(cursor, codage, 2, &offset);
	if ((codage & 0xC) == 8)
		third_arg = get_third_arg(cursor, codage, 2, &offset);
	else if ((codage & 0xC) == 4)*/
	third_arg = get_third_arg(cursor, codage, 2, &offset);

	if((codage & 0x30) == 0x10 && (codage & 0xC) == 4)
	{
		CHECK_REG(&cursor, second_arg, 2, 1, 3);
		CHECK_REG(&cursor, third_arg, 2, 1, 3);
		address = cursor->cur_pos + ((int)(cursor->reg[second_arg - 1] + cursor->reg[third_arg - 1]) % IDX_MOD);
	}
	else if ((codage & 0x30) != 0x10 && (codage & 0xC) == 4)
	{
		CHECK_REG(&cursor, third_arg, 2, 1, 3);
		address = cursor->cur_pos + ((second_arg + (int)cursor->reg[third_arg - 1]) % IDX_MOD);
	}
	else if ((codage & 0x30) == 0x10 && (codage & 0xC) != 4)
	{
		CHECK_REG(&cursor, second_arg, 2, 1, 3);
		address = cursor->cur_pos + (((int)cursor->reg[second_arg - 1] + third_arg - 1) % IDX_MOD);
	}
	else
		address = cursor->cur_pos + (second_arg + third_arg) % IDX_MOD;
	write_amount_of_bytes_data(address, &cursor->reg[src_reg - 1], 4, cursor->color);
	if (g_vm->ver == 1)
		print_sti(cursor, src_reg, second_arg, third_arg);
	move_cursor(cursor, 2, 1, 3);
}

int		count_invalid_steps(unsigned char codage, int label_size, int args)
{
	int	steps;

	steps = 0;
	if ((codage & 0xC0) == 192)
		steps += 2;
	else if ((codage & 0x80) == 128)
		steps += label_size;
	else if ((codage & 0x40) == 64)
		steps += 1;
	if (args >= 2)
	{
		if ((codage & 0x30) == 48)
			steps += 2;
		else if ((codage & 0x20) == 32)
			steps += label_size;
		else if ((codage & 0x10) == 16)
			steps += 1;
		if (args == 3)
		{
			if ((codage & 0xC) == 12)
				steps += 2;
			else if ((codage & 0x8) == 8)
				steps += label_size;
			else if ((codage & 0x4) == 4)
				steps += 1;
		}	
	}
	return (steps);
}
void	lld(t_cursor *cursor)
{
	unsigned char	codage;
	int				value;
	unsigned char	reg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	reg = (codage >= 144 && codage <= 159) ? GET_CUR_POS_BYTE(&cursor, 6) : GET_CUR_POS_BYTE(&cursor, 4);
	if (!((codage >= 144 && codage <= 159) || (codage >= 208 && codage <= 223)) || (reg > REG_NUMBER || reg == 0))
	{
		move_cursor(cursor, 4, 1, 2);
		return ;
	}
	if (codage >= 144 && codage <= 159)
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 6), 4, 1, 2);
		value = get_int_data(cursor->cur_pos + 2);
		reg = GET_CUR_POS_BYTE(&cursor, 6);
		cursor->reg[reg - 1] = value;		
	}
	else
	{
		CHECK_REG(&cursor, GET_CUR_POS_BYTE(&cursor, 4), 4, 1, 2);
		value = get_int_data(arena_truncation(cursor->cur_pos + get_short_data(cursor->cur_pos + 2)));
		cursor->reg[reg - 1] = value;		
	}
	if (g_vm->ver == 1)
		ft_printf("P %4d | lld %d r%d\n", cursor->cursror_id, value, reg);
	move_cursor(cursor, 4, 1, 2);
}


void	fork_lfork(t_cursor *cursor, int selector)
{
	t_cursor	new;
	short		address;

	new = *cursor;
	if (selector == 0)
		address = get_short_data(cursor->cur_pos + 1) % IDX_MOD;
	else
		address = get_short_data(cursor->cur_pos + 1);
	new.cur_pos = cursor->cur_pos + address;
	new.operation_code = '\0';
	cursor->operation_code = '\0';
	if (g_vm->ver == 1 && selector == 0)
		ft_printf("P %4d | fork %d (%d)\n", cursor->cursror_id, address, new.cur_pos);
	else if (g_vm->ver == 1 && selector >= 1)
		ft_printf("P %4d | lfork %d (%d)\n", cursor->cursror_id, address, new.cur_pos);
	move_cursor(cursor, 2, 0, 1);
	make_one_new_cursor(new);
}

void	aff(t_cursor *cursor)
{
	unsigned char	dest_reg;
	char			*temp;
	char			out;
	int				i;

	temp = NULL;
	dest_reg = GET_CUR_POS_BYTE(&cursor, 1);
	CHECK_REG(&cursor, dest_reg, 4, 0, 1);
	if (g_vm->vis)
	{
		i = -1;
		while (cursor->player_id != PLAYER(++i).identifier)
			;
		if (!PLAYER(i).aff_out)
		{
			PLAYER(i).aff_out = (char *)malloc(sizeof(char) * 2);
			ft_bzero(PLAYER(i).aff_out, 2);
			PLAYER(i).aff_out[0] = cursor->reg[dest_reg - 1] & 256;
		}
		else
		{
			temp = PLAYER(i).aff_out;
			out = cursor->reg[dest_reg - 1] % 256;
			PLAYER(i).aff_out = ft_strjoin(PLAYER(i).aff_out, &out);
			free(temp);
		}
	}
	else
		ft_printf("Player #%u out: %c", cursor->cursror_id, cursor->reg[dest_reg - 1] % 256);
	move_cursor(cursor, 2, 0, 1);
}
