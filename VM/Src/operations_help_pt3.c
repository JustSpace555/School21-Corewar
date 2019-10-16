/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_help_pt3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:33 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 13:05:33 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

void			make_one_new_cursor(t_cursor cursor)
{
	t_cursors_list	*current;
	int				i;

	current = make_new_cursors_list();
	current->next = g_cursors;
	g_cursors = current;
	current->cursor = cursor;
	current->cursor.cursror_id = g_vm->cursors_id_iter++;
	g_battlefield[cursor.cur_pos].cursor = true;
	i = 0;
	while (g_players[i].identifier != cursor.player_id)
		i++;
	g_players[i].amount_cursors++;
	g_cursors_amount++;
}
