#include "../Headers/virtual_header.h"

void	move_cursor(t_cursor *cursor, int new_value)
{
	g_battlefield[cursor->cur_pos].cursor = false;
	cursor->cur_pos += new_value;
	g_battlefield[cursor->cur_pos].cursor = true;
}
