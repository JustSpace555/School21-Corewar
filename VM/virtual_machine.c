/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:18:45 by cheller           #+#    #+#             */
/*   Updated: 2019/08/30 14:18:46 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_header.h"

int 	virual_machine(int amount_players, char **files_champoins)
{
	int 		i;
	int 		fd;
	t_player	*players;

	players = malloc(sizeof(t_player*) * amount_players);
	i = 0;
	while (++i < amount_players + 1)
	{
		fd = open(files_champoins[i], O_RDONLY, 1);
		while (get_next_line(fd, &players->code))
			ft_putstr(players->code);
	}
	return (1);
}