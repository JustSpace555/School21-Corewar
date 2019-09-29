#include "../Headers/virtual_header.h"

void	fork_lfork(t_cursor *cursor, int selector, t_vm *vm)
{
	t_cursor	new;

	new = *cursor;
	if (selector == 0)
		new.cur_pos = cursor->cur_pos + get_short_data(cursor->cur_pos + 1) % IDX_MOD;
	else
		new.cur_pos = cursor->cur_pos + get_short_data(cursor->cur_pos + 1);
	if (vm->ver == 1 && selector == 0)
		ft_printf("P %4d | fork %d (%d)\n", cursor->id, new.cur_pos, cursor->cur_pos + new.cur_pos % IDX_MOD);
	else if (vm->ver == 1 && selector >= 1)
		ft_printf("P %4d | lfork %d (%d)\n", cursor->id, new.cur_pos, cursor->cur_pos + new.cur_pos);
	make_one_new_cursor(new);
	move_cursor(cursor, 2, 0);
}

void	aff(t_cursor *cursor, t_vm *vm)
{
	unsigned char	dest_reg;

	dest_reg = GET_CUR_POS_BYTE(&cursor, 1);
	CHECK_REG(&cursor, dest_reg, 4, 0);
	ft_printf("%c", cursor->reg[dest_reg - 1] % 256);
	move_cursor(cursor, 2, 0);
}
