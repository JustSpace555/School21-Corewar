/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_parser_help_pt2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:38 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/16 12:39:51 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

void	make_g_player_name(int amount_bytes, uint8_t buffer[4],
										int i, int *string_size)
{
	if (amount_bytes > BYTES_AFTER_HEADER &&
			amount_bytes <= BYTES_AFTER_NAME)
		copy_bytes_to_string(g_players[i].name, buffer,
					*string_size, *string_size += 4);
}

int		make_g_player_size(int amount_bytes, uint8_t buffer[4], int i)
{
	if (amount_bytes > BYTES_AFTER_NAME + NULL_BYTES &&
						amount_bytes <= BYTES_AFTER_CODE_SIZE)
	{
		g_players[i].code_size = make_4_byte_int(buffer);
		if (g_players[i].code_size > CHAMP_MAX_SIZE)
		{
			ft_fprintf(2, "Error: File %s has too large code \
(%d bytes > %d bytes)\n", g_players[i].file_name, g_players[i].code_size, CHAMP_MAX_SIZE);
			return (0);
		}
		if (g_players[i].code_size == 0)
		{
			ft_fprintf(2, "Error: File %s is too small to be a champion\n",
													g_players[i].file_name);
			return (0);
		}
	}
	return (1);
}

void	make_g_player_comment(int amount_bytes, uint8_t buffer[4],
											int i, int *string_size)
{
	if (amount_bytes > BYTES_AFTER_CODE_SIZE &&
			amount_bytes <= BYTES_AFTER_COMMENT)
		copy_bytes_to_string(g_players[i].comment, buffer,
						*string_size, *string_size += 4);
}

void	make_g_player_code(int amount_bytes, uint8_t buffer[4],
										int i, int *string_size)
{
	if (amount_bytes > BYTES_AFTER_COMMENT + NULL_BYTES)
	{
		if (!g_players[i].code)
		{
			g_players[i].code = (char *)malloc(sizeof(char) *
									g_players[i].code_size);
			ft_bzero(g_players[i].code, g_players[i].code_size);
		}
		copy_bytes_to_string(g_players[i].code, buffer,
					*string_size, g_players[i].code_size);
		*string_size += 4;
	}
}

void	initialize_one_g_player(int i)
{
	g_players[i].name = (char *)malloc(sizeof(char) * PROG_NAME_LENGTH);
	g_players[i].comment = (char *)malloc(sizeof(char) * COMMENT_LENGTH);
	ft_bzero(g_players[i].name, PROG_NAME_LENGTH);
	ft_bzero(g_players[i].comment, COMMENT_LENGTH);
	g_players[i].identifier = g_vm->plr_nbr[i].identifier;
}
