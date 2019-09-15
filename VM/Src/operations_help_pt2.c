#include "../Headers/virtual_header.h"

void			move_cursor(t_cursor *cursor, int label_size, int byte_val)
{
	int	skip;

	if (byte_val)
		skip = get_amount_bytes_to_skip(GET_CUR_POS_BYTE(&cursor, 1), label_size) + 1;
	else
		skip = label_size;
	g_battlefield[cursor->cur_pos].cursor = false;
	cursor->cur_pos += skip + 1;
	g_battlefield[cursor->cur_pos].cursor = true;
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

void			*get_amount_of_bytes_data(short addres, int amount_for_read)
{
	static unsigned short	temp_1;
	static unsigned int		temp_2;
	int						i;

	temp_1 = 0;
	temp_2 = 0;
	if (amount_for_read == 2)
	{
		temp_1 |= GET_BYTE(addres);
		temp_1 <<= 8;
		temp_1 |= GET_BYTE(addres + 1);
		return (&temp_1);
	}
	i = -1;
	while (++i < 4)
	{
		temp_2 |= GET_BYTE(addres + i);
		if (i <= 2)
			temp_2 <<= 8;
	}
	return(&temp_2);
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
