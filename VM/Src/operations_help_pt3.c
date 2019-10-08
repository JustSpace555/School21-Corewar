#include "../Headers/virtual_header.h"

void	make_one_new_cursor(t_cursor cursor)
{
	t_cursors_list	*current;
	int				i;

	current = g_cursors;
	while (current->next)
		current = current->next;
	current->next = make_new_cursors_list();
	current->next->cursor = cursor;
	current->next->cursor.cursror_id = g_cursors_amount;
	g_battlefield[cursor.cur_pos].cursor = true;
	i = 0;
	while (PLAYER(i).identifier != cursor.player_id)
		i++;
	PLAYER(i).amount_cursors++;
	g_cursors_amount++;
}
