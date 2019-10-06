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
		else
			cursor->cycle_exec = 0;
	}
	cursor->cycle_exec = (cursor->cycle_exec > 0) ? --cursor->cycle_exec : 0;
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
		else if (cursor->operation_code == 10)
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
			move_cursor(cursor, 0, 0, 0);
		cursor->operation_code = '\0';
	}
}

void	introduce(void)
{
	int	i;

	i = -1;
	ft_printf("Introducing contestants...\n");
	while (++i < g_vm->amount_players)
		ft_printf("* Player %d, weighting %d bytes, \"%s\" (\"%s\") !\n",
			PLAYER(i).identifier, PLAYER(i).code_size,
			PLAYER(i).name, PLAYER(i).comment);
}

void	vm_check(t_cycles_to_die *repeate)
{
	int	i;

	AMOUNT_CHECKS++;
	check_alive_cursors();
	if (CTD <= 0)
		g_cursors_amount = 0;
	i = -1;
	while (++i < g_vm->amount_players)
		PLAYER(i).nbr_live = 0;
	repeate->num_p_r = CTD;
	if (CTD == repeate->num_r && CTD == repeate->num_p_r)
		repeate->amount_of_repeate++;
	else
		repeate->amount_of_repeate = 0;
	if (repeate->amount_of_repeate >= MAX_CHECKS || g_amount_live_operations >= NBR_LIVE)
	{
		if (repeate->amount_of_repeate >= MAX_CHECKS && g_amount_live_operations >= NBR_LIVE)
			CTD -= CYCLE_DELTA;
		CTD -= CYCLE_DELTA;
		repeate->num_r = CTD;
		repeate->amount_of_repeate = 0;
		if (repeate->amount_of_repeate >= MAX_CHECKS)
			repeate->amount_of_repeate = 0;
	}
	g_amount_live_operations = 0;
	LAST_CYCLE_CHECK = CURRENT_CYCLE;
	if (g_vm->ver == 2)
		ft_printf("Cycle to die is now %d\n", CTD);
}

void	process_operation(void)
{
	int	i;

	i = -1;
	while(++i < g_cursors_amount)
	{
		choose_operaion(&g_cursors[i], GET_BYTE(g_cursors[i].cur_pos));
		exec_operation(&g_cursors[i]);
	}
}

void	virtual_machine(void)
{
	t_cycles_to_die	repeate;
	SDL_FRect		cell;

	initialize_battlefield();
	fill_battlefield();
	initialize_cursors();
	initialise_main_info(&repeate);
	introduce();
	if (g_vm->vis == 1 && !init())
		return ;
	if (g_vm->dump == 0)
	{
		print_battlefield();
		free_all();
		return ;
	}
	while (!VIS_QUIT && g_cursors_amount > 0)
	{
		if (g_vm->vis == 1)
			visualisator_event();
		if (!VIS_PAUSE)
		{
			CURRENT_CYCLE++;
			if (g_vm->ver == 2)
				ft_printf("It is now cycle %d\n", CURRENT_CYCLE);
			process_operation();
			if (g_vm->vis == 1)
			{
				push_to_render_battlefield();
				push_info(repeate.amount_of_repeate, "**Running**");
				SDL_RenderPresent(g_main_render);
				// SDL_Delay(SCREEN_TICKS_PER_FRAME / amount_checks);
			}
			if (CURRENT_CYCLE - LAST_CYCLE_CHECK >= CTD || CTD <= 0)
				vm_check(&repeate);
			if (CTD > 0 && g_vm->dump >= 0 && g_vm->dump == CURRENT_CYCLE)
			{
				print_battlefield();
				free_all();
				return ;
			}
		}
		else
		{
			push_to_render_battlefield();
			push_info(repeate.amount_of_repeate, "**Pause**");
			SDL_RenderPresent(g_main_render);
		}
	}
	push_winner(repeate);
	free_all();
}
