#include "../Headers/virtual_header.h"

void	free_g_players(void)
{
	int	i;

	i = -1;
	while (++i < g_vm->amount_players)
	{
		free(PLAYER(i).code);
		free(PLAYER(i).comment);
		free(PLAYER(i).name);
		if (PLAYER(i).aff_out)
			free(PLAYER(i).aff_out);
	}
	free(g_players);
}

void	close_vis(void)
{
	TTF_CloseFont(g_font);
	TTF_Quit();
	SDL_DestroyRenderer(g_main_render);
	SDL_DestroyWindow(g_main_window);
	SDL_Quit();
}

void	free_cursors()
{
	t_cursors_list	*current;

	while (g_cursors)
	{
		current = g_cursors;
		g_cursors = g_cursors->next;
		free(current);
	}
}

void	free_all(void)
{
	if (g_vm->vis == 1)
		close_vis();
	free_g_players();
	free(g_vm->order_idtfrs);
	free(g_vm->plr_nbr);
	free(g_battlefield);
	free_cursors();
}

void	*print_battlefield_and_free(void)
{
	print_battlefield();
	free_all();
	return (NULL);
}
