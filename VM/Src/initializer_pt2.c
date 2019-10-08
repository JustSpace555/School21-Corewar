#include "../Headers/virtual_header.h"

void	fill_battlefield(void)
{
	int		i;
	int		j;
	float	diff;
	float	temp;
	int		byte;

	diff = (float)MEM_SIZE / g_vm->amount_players;
	temp = diff;
	i = -1;
	byte = 0;
	while (++i < g_vm->amount_players)
	{
		g_players[i].start_position = byte;
		g_battlefield[byte].cursor = true;
		j = -1;
		while (++j < PLAYER(i).code_size)
		{
			g_battlefield[byte].code = PLAYER(i).code[j];
			choose_color(&g_battlefield[byte], i);
			byte++;
		}
		while ((float)byte < diff && byte < MEM_SIZE)
		{
			g_battlefield[byte].color_b = 111;
			g_battlefield[byte].color_g = 111;
			g_battlefield[byte].color_r = 111;
			g_battlefield[byte].code = 0x0;
			g_battlefield[byte].color = 'n';
			byte++;
		}
		diff += temp;
	}
}

void	initialise_main_info(t_cycles_to_die *repeate)
{
	CURRENT_CYCLE = 0;
	CTD = CYCLE_TO_DIE;
	LAST_CYCLE_CHECK = 0;
	AMOUNT_CHECKS = 1;
	VIS_QUIT = 0;
	VIS_PAUSE = 0;
	repeate->num_r = CYCLE_TO_DIE;
	repeate->num_p_r = CYCLE_TO_DIE;
	repeate->amount_of_repeate = 0;
}
