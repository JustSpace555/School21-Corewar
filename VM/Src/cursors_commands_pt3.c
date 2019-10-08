#include "../Headers/virtual_header.h"

void	sti(t_cursor *cursor)
{
	unsigned char	codage;
	int				src_reg;
	int				address;
	int				second_arg;
	int				third_arg;
	unsigned short	offset;

	offset = 3;
	codage = GET_CUR_POS_BYTE(&cursor, 1);
	src_reg = GET_CUR_POS_BYTE(&cursor, 2);
	second_arg = 0;
	third_arg = 0;
	if ((codage & 0xC0) != 0x40 || (codage & 0x30) == 0 ||
		(codage & 0xC) == 0xC || (codage & 0xC) == 0 ||
		src_reg > REG_NUMBER || src_reg == 0)
	{
		move_cursor(cursor, 2, codage, 3);
		return ;
	}
	second_arg = (int)get_second_arg(cursor, codage, 2, &offset);
	third_arg = (int)get_third_arg(cursor, codage, 2, &offset);
	if (g_vm->ver == 1)
			print_sti(cursor, src_reg, second_arg, third_arg);
	if (check_reg_write_arg(cursor, codage, &second_arg, 2) &&
		check_reg_write_arg(cursor, codage, &third_arg, 3))
	{
		address = cursor->cur_pos + (second_arg + third_arg) % IDX_MOD;
		write_int_data(address, cursor->reg[src_reg - 1], cursor->color);
	}
	move_cursor(cursor, 2, codage, 3);
}

void	lld(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	offset;
	int				f_arg;
	int				s_arg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if ((codage & 0xC0) == 0 || (codage & 0xC0) == 0x40 ||
								(codage & 0x30) != 0x10)
	{
		move_cursor(cursor, 4, codage, 2);
		return ;
	}
	offset = 2;
	f_arg = get_first_arg(cursor, codage, 4, &offset); //убрать усечение % IDX_MOD
	s_arg = get_second_arg(cursor, codage, 4, &offset);
	if (check_reg(s_arg))
	{
		cursor->reg[s_arg - 1] = f_arg;
		if (g_vm->ver == 1)
			ft_printf("P %4d | lld %d r%d\n", cursor->cursror_id,
													f_arg, s_arg);
	}
	move_cursor(cursor, 4, codage, 2);
}

void	lldi(t_cursor *cursor)
{
	unsigned char	codage;
	unsigned short	offset;
	int				f_arg;
	int				s_arg;
	int				t_arg;

	codage = GET_CUR_POS_BYTE(&cursor, 1);
	if ((codage & 0xC0) == 0 || (codage & 0x30) == 0x30 ||
		(codage & 0x30) == 0 || (codage & 0xC) != 4)
	{
		move_cursor(cursor, 2, codage, 3);
		return ;
	}
	offset = 2;
	f_arg = (int)get_first_arg(cursor, codage, 2, &offset);
	s_arg = (int)get_second_arg(cursor, codage, 2, &offset);
	t_arg = (int)get_third_arg(cursor, codage, 2, &offset);
	if (!check_reg(t_arg))
	{
		if (!check_reg_write_arg(cursor, codage, &f_arg, 1) ||
			!check_reg_write_arg(cursor, codage, &s_arg, 2))
		{
			move_cursor(cursor, 2, codage, 3);
			return ;
		}
		if ((codage & 0xC0) == 0xC0)
			cursor->reg[t_arg - 1] = get_int_data(cursor->cur_pos +
													f_arg % IDX_MOD);
		else
			cursor->reg[t_arg - 1] = get_int_data(cursor->cur_pos +
													f_arg + s_arg);
	}
	move_cursor(cursor, 2, codage, 3);
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
		ft_printf("P %4d | fork %d (%d)\n", cursor->cursror_id,
											address, new.cur_pos);
	else if (g_vm->ver == 1 && selector >= 1)
		ft_printf("P %4d | lfork %d (%d)\n", cursor->cursror_id,
											address, new.cur_pos);
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
	if (check_reg(dest_reg))
	{
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
			ft_printf("Player #%u out: %c", cursor->cursror_id,
											cursor->reg[dest_reg - 1] % 256);
	}
	move_cursor(cursor, 2, 0, 1);
}
