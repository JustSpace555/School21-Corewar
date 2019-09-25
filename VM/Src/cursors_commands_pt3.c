#include "../Headers/virtual_header.h"

void	fork_lfork(t_cursor *cursor, int selector)
{
	t_cursor	new;

	new = *cursor;
	if (selector == 0)
		new.cur_pos = get_short_data(cursor->cur_pos + 1) % IDX_MOD;
	else
		new.cur_pos = get_short_data(cursor->cur_pos + 1);
	make_one_new_cursor(new);
	move_cursor(cursor, 2, 0);
}

void	aff(t_cursor *cursor)
{
	unsigned char	dest_reg;

	dest_reg = GET_CUR_POS_BYTE(&cursor, 1);
	CHECK_REG(&cursor, dest_reg, 4, 0);
	ft_printf("%c", cursor->reg[dest_reg - 1] % 256);
	move_cursor(cursor, 2, 0);
}
