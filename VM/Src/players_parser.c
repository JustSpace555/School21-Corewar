/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:44 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 13:05:45 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

int		parse_champion_file_byte(char *champion_file,
								int i, int *amount_bytes)
{
	int		fd;
	uint8_t buffer[4];
	int		string_size;

	initialize_one_g_player(i);
	if (!check_fd(&fd, champion_file))
		return (0);
	while (read(fd, buffer, 4))
	{
		*amount_bytes += 4;
		zeroing_string_size(&string_size, *amount_bytes);
		if (!if_header_bytes(*amount_bytes, buffer))
			return (0);
		make_g_player_name(*amount_bytes, buffer, i, &string_size);
		if (!make_g_player_size(*amount_bytes, buffer, i))
			return (0);
		make_g_player_comment(*amount_bytes, buffer, i, &string_size);
		make_g_player_code(*amount_bytes, buffer, i, &string_size);
	}
	close(fd);
	return (1);
}

int		players_parser(char **files_champions)
{
	int			i;
	int			amount_bytes;

	initialize_g_players();
	i = -1;
	while (++i < g_vm->amount_players)
	{
		amount_bytes = 0;
		if (!parse_champion_file_byte(files_champions[i], i, &amount_bytes))
			return (0);
	}
	if (!check_for_overflow())
		return (0);
	return (1);
}
