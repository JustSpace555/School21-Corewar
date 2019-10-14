/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:01 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 13:05:02 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

int		ft_is_strdigit(char *str)
{
	if (!str || *str == '\0')
		return (-1);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

void	zeroing_cursors_args(int *plr_id)
{
	int	i;

	CURSOR.bytes_to_next_op = 0;
	CURSOR.carry = false;
	CURSOR.cur_pos = PLAYER(--(*plr_id)).start_position;
	CURSOR.cycle_exec = 0;
	CURSOR.player_id = PLAYER(*plr_id).identifier;
	CURSOR.cursror_id = PLAYER(*plr_id).identifier;
	CURSOR.last_alive = 0;
	CURSOR.operation_code = 0;
	CURSOR.reg[0] = -PLAYER(*plr_id).identifier;
	CURSOR.color = g_battlefield[CURSOR.cur_pos].color;
	g_vm->cursors_id_iter++;
	i = 0;
	while (++i < 16)
		CURSOR.reg[i] = 0;
}

void	vis_and_check(t_cycles_to_die *repeate)
{
	if (g_vm->vis == 1)
		push_vis(*repeate, "**Running**");
	if (CURRENT_CYCLE - LAST_CYCLE_CHECK >= CTD || CTD <= 0)
		vm_check(repeate);
}

void	process_operation(void)
{
	t_cursors_list	*current;

	current = g_cursors;
	while (current)
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
