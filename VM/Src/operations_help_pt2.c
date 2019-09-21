#include "../Headers/virtual_header.h"

void			move_cursor(t_cursor *cursor, int label_size, int byte_val)
{
	int	skip;

	if (byte_val)
		skip = get_amount_bytes_to_skip(GET_CUR_POS_BYTE(&cursor, 1), label_size) + 1;
	else
		skip = label_size;
	g_battlefield[cursor->cur_pos].cursor = false;
	g_battlefield[cursor->cur_pos].cursor_color = '\0';
	if (label_size >= 0)
		cursor->cur_pos += skip + 1;
	else
		cursor->cur_pos += skip;
	if (cursor->cur_pos < MEM_SIZE)
	{
		g_battlefield[cursor->cur_pos].cursor = true;
		g_battlefield[cursor->cur_pos].cursor_color = cursor->color;
	}
}

void			make_one_new_cursor(t_cursor cursor)
{
	t_cursor	*new;
	t_cursor	*temp;
	int			i;

	new = (t_cursor *)malloc(sizeof(t_cursor) * (g_cursors_amount + 1));
	i = -1;
	while (++i < g_cursors_amount)
		new[i] = g_cursors[i];
	new[i] = cursor;
	temp = g_cursors;
	g_cursors = new;
	free(temp);
	g_cursors_amount++;
}

short			get_short_data(short addres)
{
	short	res;

	res = 0;
	res |= GET_BYTE(addres);
	res <<= 8;
	res |= GET_BYTE(addres + 1);
	return (res);
}

unsigned int	get_int_data(short addres)
{
	unsigned short	res;
	int				i;

	res = 0;
	i = -1;
	while (++i < 4)
	{
		res |= GET_BYTE(addres + i);
		if (i <= 2)
			res <<= 8;
	}
	return (res);
}
