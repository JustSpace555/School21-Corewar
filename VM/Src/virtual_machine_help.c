#include "../Headers/virtual_header.h"

void	free_all(void)
{
	int				i;
	t_cursors_list	*current;

	if (g_vm->vis == 1)
	{
		TTF_CloseFont(g_font);
		TTF_Quit();
		SDL_DestroyRenderer(g_main_render);
		SDL_DestroyWindow(g_main_window);
		SDL_Quit();
	}
	i = -1;
	while (++i < g_vm->amount_players)
	{
		free(PLAYER(i).code);
		free(PLAYER(i).comment);
		free(PLAYER(i).name);
		if (PLAYER(i).aff_out)
			free(PLAYER(i).aff_out);
	}
	free(g_vm->order_idtfrs);
	free(g_vm->plr_nbr);
	free(g_battlefield);
	while (g_cursors)
	{
		current = g_cursors;
		g_cursors = g_cursors->next;
		free(current);
	}
}

void	check_alive_cursors(void)
{
	int				i;
	t_cursors_list	*current;
	t_cursors_list	*prev;

	current = g_cursors;
	prev = g_cursors;
	while (current)
	{
		if (!(CURRENT_CYCLE - current->cursor.last_alive < CURRENT_CYCLE -
			LAST_CYCLE_CHECK || (LAST_CYCLE_CHECK == 0 &&
								current->cursor.last_alive != 0)))
		{
			i = 0;
			g_battlefield[current->cursor.cur_pos].cursor = false;
			while (PLAYER(i).identifier != current->cursor.player_id)
				i++;
			PLAYER(i).amount_cursors--;
			current = current->next;
			if (prev->next == current)
			{
				if (prev == g_cursors)
					g_cursors = g_cursors->next;
				free(prev);
				prev = current;
			}
			else
			{
				free(prev->next);
				prev->next = current;
			}
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	push_winner_terminal(void)
{
	int	i;
	int	id;
	int	max;

	i = -1;
	max = 0;
	while(++i < g_vm->amount_players)
		if (PLAYER(i).last_alive > max)
		{
			max = PLAYER(i).last_alive;
			id = i;
		}
	ft_printf("Contestant %d, \"%s\", has won !\n", id + 1, PLAYER(id).name);
}

void	push_winner(t_cycles_to_die repeate)
{
	SDL_Event	event;

	if (g_vm->vis == 1 && !VIS_QUIT)
	{
		VIS_PAUSE = 0;
		VIS_QUIT = 0;
		push_to_render_battlefield();
		push_info(repeate.amount_of_repeate, "**Pause**");
		push_winner_vis();
		SDL_RenderPresent(g_main_render);
		while (!VIS_QUIT && !VIS_PAUSE)
			while(SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
					&& event.key.keysym.sym == SDLK_ESCAPE))
					VIS_QUIT = 1;
				if (event.type == SDL_KEYDOWN
					&& event.key.keysym.sym == SDLK_SPACE)
					VIS_PAUSE = 1;
			}
	}
	else if(g_vm->vis != 1 && !VIS_QUIT)
		push_winner_terminal();
}

void	*print_battlefield_and_free(void)
{
	print_battlefield();
	free_all();
	return (NULL);
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
