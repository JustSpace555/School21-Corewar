#include "../Headers/virtual_header.h"

void	fill_battlefield(t_vm *vm)
{
	int		i;
	int		j;
	float	diff;
	float	temp;
	int		byte;

	diff = (float)MEM_SIZE / vm->amount_players;
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

void	exec_operation(t_cursor *cursor, int current_cycle, t_vm *vm)
{
	if (cursor->cycle_exec == 0)
	{
		if (cursor->operation_code == 1)
			live(cursor, current_cycle, vm);
		else if (cursor->operation_code == 2)
			ld(cursor, vm);
		else if (cursor->operation_code == 3)
			st(cursor, vm);
		else if (cursor->operation_code == 4)
			add(cursor, vm);
		else if (cursor->operation_code == 5)
			sub(cursor, vm);
		else if (cursor->operation_code == 6)
			and_or_xor(cursor, 0, vm);
		else if (cursor->operation_code == 7)
			and_or_xor(cursor, 1, vm);
		else if (cursor->operation_code == 8)
			and_or_xor(cursor, 2, vm);
		else if (cursor->operation_code == 9)
			zjmp(cursor, vm);
		else if (cursor->operation_code == 10)
			ldi_lldi(cursor, 0, vm);
		else if (cursor->operation_code == 11)
			sti(cursor, vm);
		else if (cursor->operation_code == 12)
			fork_lfork(cursor, 0, vm);
		else if (cursor->operation_code == 13)
			lld(cursor, vm);
		else if (cursor->operation_code == 14)
			ldi_lldi(cursor, 1, vm);
		else if (cursor->operation_code == 15)
			fork_lfork(cursor, 1, vm);
		else if (cursor->operation_code == 16)
			aff(cursor, vm);
		else
			move_cursor(cursor, 0, 0, 0);
		cursor->operation_code = '\0';
	}
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

void	ft_pause(void)
{
	SDL_Event	event;

	while (1)
		if(SDL_PollEvent(&event))
			if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.sym == SDLK_RETURN
					|| event.key.keysym.sym == SDLK_ESCAPE)
					break ;
}

void	virtual_machine(t_vm *vm)
{
	int				i;
	int				current_cycle;
	int				cycle_to_die;
	int				last_cycle_check;
	t_cycles_to_die	repeate;
	int				amount_checks;
	t_bool			quit;
	t_bool			pause;
	SDL_Event		event;
	SDL_FRect		cell;
	TTF_Font		*font;

	initialize_battlefield();
	fill_battlefield(vm);
	initialize_cursors(vm->amount_players);
	introduce(vm);
	last_cycle_check = 0;
	repeate.num_r = CYCLE_TO_DIE;
	repeate.num_p_r = CYCLE_TO_DIE;
	repeate.amount_of_repeate = 0;
	cycle_to_die = CYCLE_TO_DIE;
	current_cycle = 0;
	quit = false;
	pause = false;
	amount_checks = 1;
	if (vm->vis == 1 && !init())
		return ;
	if (vm->dump == 0)
	{
		print_battlefield();
		return ;
	}
	if (vm->vis == 1 && !(font = TTF_OpenFont("visualisator/InputMono-Regular.ttf", 15)))
	{
		ft_printf("%s\n", TTF_GetError());
		return ;
	}
	cell.w = (float)(SCREEN_WIDTH - INFORMATION_SIZE) / 64;
	cell.h = (float)SCREEN_HEIGHT / 64;
	while (!quit && g_cursors_amount > 0)
	{
		if (vm->vis == 1)
			while(SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
					&& event.key.keysym.sym == SDLK_ESCAPE))
					quit = true;
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
				{
					if (pause == true)
						pause = false;
					else
						pause = true;
				}
			}
		if (!pause)
		{
			current_cycle++;
			i = -1;
			while(++i < g_cursors_amount)
			{
				choose_operaion(&g_cursors[i], GET_BYTE(g_cursors[i].cur_pos));
				exec_operation(&g_cursors[i], current_cycle, vm);
			}
			if (vm->vis == 1)
			{
				push_to_render_battlefield(cell);
				push_info(current_cycle, cycle_to_die, font, vm->amount_players, repeate.amount_of_repeate, "**Running**");
				SDL_RenderPresent(g_main_render);
				// SDL_Delay(SCREEN_TICKS_PER_FRAME / amount_checks);
			}
			if (current_cycle - last_cycle_check >= cycle_to_die || cycle_to_die <= 0)
			{
				amount_checks++;
				check_alive_cursors(last_cycle_check, current_cycle);
				i = -1;
				while (++i < vm->amount_players)
					PLAYER(i).nbr_live = 0;
				repeate.num_p_r = cycle_to_die;
				if (cycle_to_die == repeate.num_r && cycle_to_die == repeate.num_p_r)
					repeate.amount_of_repeate++;
				else
					repeate.amount_of_repeate = 0;
				if (repeate.amount_of_repeate >= MAX_CHECKS || g_amount_live_operations >= NBR_LIVE)
				{
					if (repeate.amount_of_repeate >= MAX_CHECKS && g_amount_live_operations >= NBR_LIVE)
						cycle_to_die -= CYCLE_DELTA;
					cycle_to_die -= CYCLE_DELTA;
					repeate.num_r = cycle_to_die;
					repeate.amount_of_repeate = 0;
					if (repeate.amount_of_repeate >= MAX_CHECKS)
						repeate.amount_of_repeate = 0;
				}
				g_amount_live_operations = 0;
				last_cycle_check = current_cycle;
			}
			if (cycle_to_die > 0 && vm->dump >= 0 && vm->dump == current_cycle)
			{
				print_battlefield();
				return ;
			}
		}
		else
		{
			push_to_render_battlefield(cell);
			push_info(current_cycle, cycle_to_die, font, vm->amount_players, repeate.amount_of_repeate, "**Pause**");
			SDL_RenderPresent(g_main_render);
		}
	}
	if (vm->vis == 1)
	{
		push_to_render_battlefield(cell);
		push_info(current_cycle, cycle_to_die, font, vm->amount_players, repeate.amount_of_repeate, "**Pause**");
		SDL_RenderPresent(g_main_render);
		push_winner(font, vm->amount_players);
	}
	else
		push_winner_terminal(vm->amount_players);
	free_all(font, vm);
	// printf("\nnum_r = %d\n", repeate.num_r);
	// printf("num_p_r = %d\n", repeate.num_p_r);
	// printf("CTD = %d\n", cycle_to_die);
	// printf("Cycles = %d\n", current_cycle);
}
