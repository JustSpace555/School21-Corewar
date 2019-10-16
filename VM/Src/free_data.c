/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:04 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/16 16:24:51 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

void	free_g_players(void)
{
	int	i;

	i = -1;
	if (g_players)
	{
		while (++i < g_vm->amount_players)
		{
			if (g_players[i].name)
				free(g_players[i].name);
			if (g_players[i].comment)
				free(g_players[i].comment);
			if (g_players[i].code)
				free(g_players[i].code);
			if (g_players[i].aff_out)
				free(g_players[i].aff_out);
		}
		free(g_players);
	}
}

void	close_vis(void)
{
	TTF_CloseFont(g_font);
	TTF_Quit();
	SDL_DestroyRenderer(g_main_render);
	SDL_DestroyWindow(g_main_window);
	SDL_Quit();
}

void	free_cursors(void)
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
	if (g_vm->order_idtfrs)
		free(g_vm->order_idtfrs);
	if (g_vm->plr_nbr)
		free(g_vm->plr_nbr);
	if (g_battlefield)
		free(g_battlefield);
	free_cursors();
	free(g_vm);
}

void	*print_battlefield_and_free(void)
{
	print_battlefield();
	return (NULL);
}
