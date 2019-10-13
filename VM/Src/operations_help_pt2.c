#include "../Headers/virtual_header.h"

void			jump_to_next_op(t_cursor *cursor, unsigned char codage,
									int label_size, int amount_arguments)
{
	int				skip;
	int				amount_cursors_cell;
	t_cursors_list	*current;

	current = g_cursors;
	skip = get_amount_bytes_to_skip(codage,
			label_size, amount_arguments) + 1;
	amount_cursors_cell = 0;
	while (current)
	{
		if (current->cursor.cur_pos == cursor->cur_pos)
			amount_cursors_cell++;
		current = current->next;
	}
	if (amount_cursors_cell == 1)
		g_battlefield[cursor->cur_pos].cursor = false;
	print_pc_movement(cursor, skip + 1);
	cursor->cur_pos += skip + 1;
	if (cursor->cur_pos >= MEM_SIZE)
		cursor->cur_pos %= MEM_SIZE;
	g_battlefield[cursor->cur_pos].cursor = true;
}

void			move_cursor(t_cursor *cursor, int skip)
{
	t_cursors_list	*current;
	int				amount_cursors_cell;

	current = g_cursors;
	amount_cursors_cell = 0;
	while (current)
	{
		if (current->cursor.cur_pos == cursor->cur_pos)
			amount_cursors_cell++;
		current = current->next;
	}
	if (amount_cursors_cell == 1)
		g_battlefield[cursor->cur_pos].cursor = false;
	cursor->cur_pos += skip;
	if (cursor->cur_pos >= MEM_SIZE)
		cursor->cur_pos %= MEM_SIZE;
	g_battlefield[cursor->cur_pos].cursor = true;
}

short			get_short_data(short addres)
{
	short	res;

	addres = arena_truncation(addres);
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
	addres = arena_truncation(addres);
	while (++i < 4)
	{
		res |= GET_BYTE((addres + i) % MEM_SIZE);
		if (i <= 2)
			res <<= 8;
	}
	return (res);
}
