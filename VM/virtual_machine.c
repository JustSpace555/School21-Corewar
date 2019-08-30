/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:18:45 by cheller           #+#    #+#             */
/*   Updated: 2019/08/30 16:42:37 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_header.h"

int	virual_machine(int amount_players, char **files_champoins)
{
	g_players = (t_player *)malloc(sizeof(t_player) * amount_players);
	print_hex_data(amount_players, files_champoins);
	return (1);
}
