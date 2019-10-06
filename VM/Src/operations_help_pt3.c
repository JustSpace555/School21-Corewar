#include "../Headers/virtual_header.h"

void	make_one_new_cursor(t_cursor cursor)
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
