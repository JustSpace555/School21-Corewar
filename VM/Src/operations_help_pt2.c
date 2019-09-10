#include "../Headers/virtual_header.h"

void	move_cursor(t_cursor *cursor, int new_value)
{
	g_battlefield[cursor->cur_pos].cursor = false;
	cursor->cur_pos += new_value;
	g_battlefield[cursor->cur_pos].cursor = true;
}

void	make_one_new_cursor(t_cursor cursor)
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
