#include "../Headers/virtual_header.h"

void			move_cursor(t_cursor *cursor, int label_size, int byte_val, int amount_arguments)
{
	int	skip;
	int	i;
	int	amount_cursors_cell;

	if (byte_val)
		skip = get_amount_bytes_to_skip(GET_CUR_POS_BYTE(&cursor, 1), label_size, amount_arguments) + 1;
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

void			make_one_new_cursor(t_cursor cursor)
{
	t_cursor	*new;
	t_cursor	*temp;
	int			i;
	int			j;

	new = (t_cursor *)malloc(sizeof(t_cursor) * (g_cursors_amount + 1));
	i = -1;
	while (++i < g_cursors_amount)
		new[i] = g_cursors[i];
	j = 0;
	while (PLAYER(j).identifier != cursor.player_id)
		j++;
	PLAYER(j).amount_cursors++;
	new[i] = cursor;
	g_cursors_amount++;
	new[i].cursror_id = g_cursors_amount;
	temp = g_cursors;
	g_cursors = new;
	free(temp);
	g_battlefield[cursor.cur_pos].cursor = true;
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
