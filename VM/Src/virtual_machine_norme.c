#include "../Headers/virtual_header.h"

void	vis_and_check(t_cycles_to_die *repeate)
{
	if (g_vm->vis == 1)
		push_vis(*repeate, "**Running**");
	if (CURRENT_CYCLE - LAST_CYCLE_CHECK >= CTD || CTD <= 0)
		vm_check(repeate);
}

void	process_operation(void)
{
	t_cursors_list	*current;

	current = g_cursors;
	while(current)
	{
		choose_operaion(&current->cursor, GET_BYTE(current->cursor.cur_pos));
		exec_operation(&current->cursor);
		current = current->next;
	}
}

void	zeroing_nbr_live(void)
{
	int	i;

	i = -1;
	while (++i < g_vm->amount_players)
		PLAYER(i).nbr_live = 0;
}
