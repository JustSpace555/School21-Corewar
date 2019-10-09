#include "../Headers/virtual_header.h"

void			fill_battlefield(void)
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
		fill_free_space_battlefield(&byte, diff);
		diff += temp;
	}
}

void			initialise_main_info(t_cycles_to_die *repeate)
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

void			initialize_all(t_cycles_to_die *repeate)
{
	initialize_battlefield();
	initialize_cursors();
	initialise_main_info(repeate);
	introduce();
}

t_cursors_list	*make_new_cursors_list(void)
{
	t_cursors_list	*new;

	new = (t_cursors_list *)malloc(sizeof(t_cursors_list));
	new->next = NULL;
	return (new);
}
