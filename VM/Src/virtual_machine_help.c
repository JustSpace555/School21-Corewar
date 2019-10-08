#include "../Headers/virtual_header.h"

void	free_all(void)
{
	int	i;

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
	free(g_cursors);
}

void	check_alive_cursors(void)
{
	int			i;
	int			j;
	int			alive_cursors;
	t_cursor	*new;
	void		*temp;

	i = -1;
	alive_cursors = 0;
	while (++i < g_cursors_amount)
		if(CURRENT_CYCLE - CURSOR(i).last_alive < CURRENT_CYCLE -
			LAST_CYCLE_CHECK || (LAST_CYCLE_CHECK == 0 &&
								CURSOR(i).last_alive != 0))
			alive_cursors++;
		else
		{
			j = 0;
			g_battlefield[CURSOR(i).cur_pos].cursor = false;
			while (PLAYER(j).identifier != CURSOR(i).player_id)
				j++;
			PLAYER(j).amount_cursors--;
		}
	if (alive_cursors == g_cursors_amount)
		return ;
	j = -1;
	new = (t_cursor *)malloc(sizeof(t_cursor) * alive_cursors);
	i = -1;
	while (++i < g_cursors_amount)
		if(CURRENT_CYCLE - CURSOR(i).last_alive < CURRENT_CYCLE -
			LAST_CYCLE_CHECK || (LAST_CYCLE_CHECK == 0 &&
								CURSOR(i).last_alive != 0))
			new[++j] = CURSOR(i);
	g_cursors_amount = alive_cursors;
	temp = g_cursors;
	g_cursors = new;
	free(temp);
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
