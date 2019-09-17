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

void	choose_operaion(t_cursor *cursor, unsigned char byte)
{
	if (cursor->cycle_exec == -1)
	{
		cursor->operation_code = byte;
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
}

void	exec_operation(t_cursor *cursor, int current_cycle)
{
	if (cursor->operation_code == 1)
		live(cursor, current_cycle);
	else if (cursor->operation_code == 2)
		ld(cursor);
	else if (cursor->operation_code == 3)
		st(cursor);
	else if (cursor->operation_code == 4)
		add(cursor);
	else if (cursor->operation_code == 5)
		sub(cursor);
	else if (cursor->operation_code == 6)
		and_or_xor(cursor, 0);
	else if (cursor->operation_code == 7)
		and_or_xor(cursor, 1);
	else if (cursor->operation_code == 8)
		and_or_xor(cursor, 2);
	else if (cursor->operation_code == 9)
		zjmp(cursor);
	else if (cursor->operation_code == 10)
		ldi_lldi(cursor, 0);
	else if (cursor->operation_code == 11)
		sti(cursor);
	else if (cursor->operation_code == 12)
		fork_lfork(cursor, 0);
	else if (cursor->operation_code == 13)
		lld(cursor);
	else if (cursor->operation_code == 14)
		ldi_lldi(cursor, 1);
	else if (cursor->operation_code == 15)
		fork_lfork(cursor, 1);
	else if (cursor->operation_code == 16)
		aff(cursor);
}

void	introduce(t_vm *vm)
{
	int	i;

	i = -1;
	ft_printf("Introducing contestants...\n");
	while (++i < vm->amount_players)
		ft_printf("* Player %d, weighting %d bytes, \"%s\" (\"%s\") !\n",
			PLAYER(i).identifier, PLAYER(i).code_size,
			PLAYER(i).name, PLAYER(i).comment);
}

void	virtual_machine(t_vm *vm)
{
	int	i;
	int	current_cycle;
	int	amount_alive_cursors;
	int	cycle_to_die;
	int	last_cycle_check;
	t_cycles_to_die	repeate;

	initialize_battlefield();
	fill_battlefield(vm);
	initialize_cursors(vm->amount_players);
	introduce(vm);
	last_cycle_check = 0;
	repeate.num_r = CYCLE_TO_DIE;
	repeate.num_p_r = CYCLE_TO_DIE;
	repeate.amount_of_repeate = 0;
	cycle_to_die = CYCLE_TO_DIE;
	current_cycle = 1;
	while (cycle_to_die > 0)
	{
		i = -1;
		while(++i < g_cursors_amount)
		{
			// system("clear");
			if ((GET_BYTE(g_cursors[i].cur_pos) == 0x0 || GET_BYTE(g_cursors[i].cur_pos) > 0x10))
				move_cursor(&g_cursors[i], 0, 0);
			else
			{
				choose_operaion(&g_cursors[i], GET_BYTE(g_cursors[i].cur_pos));
				exec_operation(&g_cursors[i], current_cycle);
			}
			// print_battlefield();
			// ft_printf("Cycle = %d\n", current_cycle);
			// system("sleep 0.01");
		}
		printf("It is now cycle %d\n", current_cycle);
		if (current_cycle - last_cycle_check >= cycle_to_die)
		{
			i = -1;
			amount_alive_cursors = 0;
			while (++i < g_cursors_amount)
				if(ft_abs(g_cursors[i].last_alive - last_cycle_check)
					< last_cycle_check ||
					(last_cycle_check == 0 && g_cursors[i].last_alive != 0))
				{
					amount_alive_cursors++;
					g_cursors[i].last_alive = 0;
				}
			repeate.num_p_r = cycle_to_die;
			if (cycle_to_die == repeate.num_r && cycle_to_die == repeate.num_p_r)
				repeate.amount_of_repeate++;
			else
				repeate.amount_of_repeate = 0;
			if (repeate.amount_of_repeate + 1 >= MAX_CHECKS || g_amount_live_operations >= NBR_LIVE)
			{
				if (repeate.amount_of_repeate >= MAX_CHECKS && g_amount_live_operations >= NBR_LIVE)
					cycle_to_die -= CYCLE_DELTA;
				cycle_to_die -= CYCLE_DELTA;
				printf("Cycle to die is now %d\n", cycle_to_die);
				repeate.num_r = cycle_to_die;
				repeate.amount_of_repeate = 0;
				if (repeate.amount_of_repeate >= MAX_CHECKS)
					repeate.amount_of_repeate = 0;
			}
			g_amount_live_operations = 0;
			last_cycle_check = current_cycle;
			if (amount_alive_cursors == 0)
				break ;
		}
		current_cycle++;
		// printf("Amount of lives = %d\n", g_amount_live_operations);
		// printf("Amount of checks = %d\n", amount_of_checks);
		// if (current_cycle <= 57955)
		// {
			// printf("num_r = %d\n", repeate.num_r);
			// printf("num_p_r = %d\n", repeate.num_p_r);
			// printf("CTD = %d\n", cycle_to_die);
		// }
		// printf("Cycles = %d\n", current_cycle);
	}
	// printf("num_r = %d\n", repeate.num_r);
	// printf("num_p_r = %d\n", repeate.num_p_r);
	// printf("CTD = %d\n", cycle_to_die);
	// printf("Cycles = %d\n", current_cycle);
}
