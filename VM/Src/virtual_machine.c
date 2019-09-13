#include "../Headers/virtual_header.h"

void	fill_battlefield(t_vm *vm)
{
	int	i;
	int	j;
	int	diff;
	int	temp;
	int	byte;

	diff = MEM_SIZE / vm->amount_players;
	temp = diff;
	i = -1;
	byte = 0;
	while (++i < vm->amount_players)
	{
		g_players[i].start_position = byte;
		g_battlefield[byte].cursor = true;
		j = -1;
		while (++j < PLAYER(i).code_size)
		{
			g_battlefield[byte].code = PLAYER(i).code[j];
			g_battlefield[byte].color = choose_color(i);
			byte++;
		}
		while (byte < MIN(diff, MEM_SIZE))
		{
			g_battlefield[byte].code = 0x0;
			g_battlefield[byte].color = '\0';
			byte++;
		}
		diff += temp;
	}
}

void	chose_operaion(t_cursor *cursor)
{
	// if (GET_BYTE(cursor->cur_pos) == 1)
}

void	virtual_machine(t_vm *vm)
{
	int	i;
	initialize_battlefield();
	initialize_cursors(vm->amount_players);
	fill_battlefield(vm);
	while (1)
	{
		i = -1;
		while(++i < g_cursors_amount)
		{
			if (GET_BYTE(g_cursors[i].cur_pos) == 0 || GET_BYTE(g_cursors[i].cur_pos > 16))
				move_cursor(&g_cursors[i], 0, 0);
			else
			{

			}
		}
	}
	print_battlefield();
}
