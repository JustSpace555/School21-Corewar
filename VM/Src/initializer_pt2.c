#include "../Headers/virtual_header.h"

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
