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
	move_cursor(cursor, 2, 0);
	make_one_new_cursor(new);
}

void	aff(t_cursor *cursor, t_vm *vm)
{
	unsigned char	dest_reg;
	char			*temp;
	char			out;
	int				i;

	temp = NULL;
	dest_reg = GET_CUR_POS_BYTE(&cursor, 1);
	CHECK_REG(&cursor, dest_reg, 4, 0);
	if (vm->vis)
	{
		i = -1;
		while (cursor->id != PLAYER(++i).identifier)
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
		ft_printf("Player #%u out: %c", cursor->id, cursor->reg[dest_reg - 1] % 256);
	move_cursor(cursor, 2, 0);
}
