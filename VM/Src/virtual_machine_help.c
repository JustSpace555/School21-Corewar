#include "../Headers/virtual_header.h"

void	choose_color(t_battlefield *cell, int i)
{
	if (i == 0)
	{
		cell->color = 'r';
		cell->color_r = 155;
	}
	else if (i == 1)
	{
		cell->color = 'y';
		cell->color_r = 155;
		cell->color_g = 155;
	}
	else if (i == 2)
	{
		cell->color = 'g';
		cell->color_g = 128;
	}
	else if (i == 3)
	{
		cell->color = 'b';
		cell->color_b = 155;
	}
	else if (i == 4)
	{
		cell->color = 'p';
		cell->color_r = 128;
		cell->color_b = 128;
	}
	else if (i == 5)
	{
		cell->color = 'c';
		cell->color_g = 155;
		cell->color_b = 155;
	}
	else if (i == 6)
	{
		cell->color = 'e';
		cell->color_r = 169;
		cell->color_g = 169;
		cell->color_b = 169;
	}
	else if (i == 7)
	{
		cell->color = 'l';
		cell->color_r = 50;
		cell->color_g = 50;
		cell->color_b = 50;
	}
}

char	choose_color_char(int i)
{
	if (i == 0)
		return('r');
	else if (i == 1)
		return('y');
	else if (i == 2)
		return('g');
	else if (i == 3)
		return('b');
	else if (i == 4)
		return('p');
	else if (i == 5)
		return('c');
	else if (i == 6)
		return('e');
	else if (i == 7)
		return ('b');
	return ('n');
}

int		choose_reverse_color(t_battlefield *cell)
{
	if (cell->color == 'r')
	{
		cell->color_r = 155;
		cell->color_g = 0;
		cell->color_b = 0;
		return (0);
	}
	else if (cell->color == 'y')
	{
		cell->color_r = 155;
		cell->color_g = 155;
		cell->color_b = 0;
		return (1);
	}
	else if (cell->color == 'g')
	{
		cell->color_r = 0;
		cell->color_g = 128;
		cell->color_b = 0;
		return (2);
	}
	else if (cell->color == 'b')
	{
		cell->color_r = 0;
		cell->color_g = 0;
		cell->color_b = 155;
		return (3);
	}
	else if (cell->color == 'p')
	{
		cell->color_r = 128;
		cell->color_g = 0;
		cell->color_b = 128;
		return (4);
	}
	else if (cell->color == 'c')
	{
		cell->color_r = 0;
		cell->color_g = 155;
		cell->color_b = 155;
		return (5);
	}
	else if (cell->color == 'e')
	{
		cell->color_r = 169;
		cell->color_g = 169;
		cell->color_b = 169;
		return (6);
	}
	else if (cell->color == 'l')
	{
		cell->color_r = 50;
		cell->color_g = 50;
		cell->color_b = 50;
		return (7);
	}
	return (8);
}

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
		if(CURRENT_CYCLE - CURSOR(i).last_alive < CURRENT_CYCLE - LAST_CYCLE_CHECK || (LAST_CYCLE_CHECK == 0 && CURSOR(i).last_alive != 0))
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
		if(CURRENT_CYCLE - CURSOR(i).last_alive < CURRENT_CYCLE - LAST_CYCLE_CHECK || (LAST_CYCLE_CHECK == 0 && CURSOR(i).last_alive != 0))
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
	if (g_vm->vis == 1 && !VIS_QUIT)
	{
		push_to_render_battlefield();
		push_info(repeate.amount_of_repeate, "**Pause**");
		SDL_RenderPresent(g_main_render);
		push_winner_vis();
	}
	else if(g_vm->vis != 1 && !VIS_QUIT)
		push_winner_terminal();
}
