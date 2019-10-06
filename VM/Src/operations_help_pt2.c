#include "../Headers/virtual_header.h"

int		check_for_cycle_exec(t_cursor *cursor)
{
	if (cursor->cycle_exec > 0)
	{
		cursor->cycle_exec--;
		if (cursor->cycle_exec > 0)
			return (-1);
	}
	cursor->cycle_exec = -1;
	return (1);
}

void			move_cursor(t_cursor *cursor, int label_size,
							unsigned char byte_val, int amount_arguments)
{
	int	skip;
	int	i;
	int	amount_cursors_cell;

	if (byte_val)
		skip = get_amount_bytes_to_skip(byte_val, label_size, amount_arguments) + 1;
	else
		skip = label_size;
	i = -1;
	amount_cursors_cell = 0;
	while (++i < g_cursors_amount)
		if (g_cursors[i].cur_pos == cursor->cur_pos)
			amount_cursors_cell++;
	if (amount_cursors_cell == 1)
		g_battlefield[cursor->cur_pos].cursor = false;
	cursor->cur_pos += skip + 1; //учесть -1, 0
	if (cursor->cur_pos >= MEM_SIZE)
		cursor->cur_pos %= MEM_SIZE;
	g_battlefield[cursor->cur_pos].cursor = true;
}

short			get_short_data(short addres)
{
	short	res;

	res = 0;
	res |= GET_BYTE(addres % MEM_SIZE);
	res <<= 8;
	res |= GET_BYTE((addres + 1) % MEM_SIZE);
	return (res);
}

unsigned int	get_int_data(short addres)
{
	unsigned int	res;
	int				i;

	res = 0;
	i = -1;
	while (++i < 4)
	{
		res |= GET_BYTE((addres + i) % MEM_SIZE);
		if (i <= 2)
			res <<= 8;
	}
	return (res);
}
