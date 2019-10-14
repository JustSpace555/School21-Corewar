#include "../Headers/virtual_header.h"

void	choose_operaion(t_cursor *cursor, unsigned char byte)
{
	if (cursor->operation_code == '\0')
		cursor->operation_code = byte;
	if (cursor->cycle_exec == 0)
	{
		if (byte == 1 || byte == 4 || byte == 5 || byte == 13)
			cursor->cycle_exec = 10;
		else if (byte == 2 || byte == 3)
			cursor->cycle_exec = 5;
		else if (byte >= 6 && byte <= 8)
			cursor->cycle_exec = 6;
		else if (byte == 9)
			cursor->cycle_exec = 20;
		else if (byte == 10 || byte == 11)
			cursor->cycle_exec = 25;
		else if (byte == 12)
			cursor->cycle_exec = 800;
		else if (byte == 14)
			cursor->cycle_exec = 50;
		else if (byte == 15)
			cursor->cycle_exec = 1000;
		else if (byte == 16)
			cursor->cycle_exec = 2;
	}
	cursor->cycle_exec = (cursor->cycle_exec > 0) ? --cursor->cycle_exec : 0;
}

void	exec_operation_pt2(t_cursor *cursor)
{
	if (cursor->operation_code == 10)
		ldi(cursor);
	else if (cursor->operation_code == 11)
		sti(cursor);
	else if (cursor->operation_code == 12)
		fork_lfork(cursor, 0);
	else if (cursor->operation_code == 13)
		lld(cursor);
	else if (cursor->operation_code == 14)
		lldi(cursor);
	else if (cursor->operation_code == 15)
		fork_lfork(cursor, 1);
	else if (cursor->operation_code == 16)
		aff(cursor);
	else
		move_cursor(cursor, 1);
}

void	exec_operation(t_cursor *cursor)
{
	if (cursor->cycle_exec == 0)
	{
		if (cursor->operation_code == 1)
			live(cursor);
		else if (cursor->operation_code == 2)
			ld(cursor);
		else if (cursor->operation_code == 3)
			st(cursor);
		else if (cursor->operation_code == 4)
			add(cursor);
		else if (cursor->operation_code == 5)
			sub(cursor);
		else if (cursor->operation_code == 6)
			and(cursor);
		else if (cursor->operation_code == 7)
			or(cursor);
		else if (cursor->operation_code == 8)
			xor(cursor);
		else if (cursor->operation_code == 9)
			zjmp(cursor);
		else
			exec_operation_pt2(cursor);
		cursor->operation_code = '\0';
	}
}

void	vm_check(t_cycles_to_die *repeate)
{
	AMOUNT_CHECKS++;
	check_alive_cursors();
	zeroing_nbr_live();
	repeate->num_p_r = CTD;
	repeate->amount_of_repeate = (CTD == repeate->num_r &&
		CTD == repeate->num_p_r) ? repeate->amount_of_repeate + 1 : 0;
	if (repeate->amount_of_repeate >= MAX_CHECKS
		|| g_amount_live_operations >= NBR_LIVE)
	{
		CTD -= CYCLE_DELTA * ((repeate->amount_of_repeate >= MAX_CHECKS
						&& g_amount_live_operations >= NBR_LIVE) ? 2 : 1);
		if (g_vm->ver == 2 || g_vm->ver == 30)
			ft_printf("Cycle to die is now %d\n", CTD);
		repeate->num_r = CTD;
		repeate->amount_of_repeate = 0;
		if (repeate->amount_of_repeate >= MAX_CHECKS)
			repeate->amount_of_repeate = 0;
	}
	g_amount_live_operations = 0;
	LAST_CYCLE_CHECK = CURRENT_CYCLE;
}

void	*virtual_machine(void)
{
	t_cycles_to_die	repeate;

	initialize_all(&repeate);
	if (g_vm->dump == 0 || (g_vm->vis == 1 && !init()))
		return (print_battlefield_and_free());
	while (!VIS_QUIT && g_cursors_amount > 0)
	{
		if (g_vm->vis == 1)
			visualisator_event();
		if (!VIS_PAUSE)
		{
			inc_current_cycle_and_print();
			process_operation();
			vis_and_check(&repeate);
			if (CTD > 0 && g_vm->dump == CURRENT_CYCLE)
				return (print_battlefield_and_free());
		}
		else
			push_vis(repeate, "**Pause**");
	}
	if (!VIS_QUIT)
		push_winner(repeate);
	free_all();
	return (NULL);
}
