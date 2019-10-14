/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_parser_help_pt2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:38 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 16:40:40 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

void	make_g_player_name(int amount_bytes, uint8_t buffer[4],
										int i, int *string_size)
{
	if (amount_bytes > BYTES_AFTER_HEADER &&
			amount_bytes <= BYTES_AFTER_NAME)
		copy_bytes_to_string(PLAYER(i).name, buffer,
					*string_size, *string_size += 4);
}

int		make_g_player_size(int amount_bytes, uint8_t buffer[4], int i)
{
	if (amount_bytes > BYTES_AFTER_NAME + NULL_BYTES &&
						amount_bytes <= BYTES_AFTER_CODE_SIZE)
	{
		PLAYER(i).code_size = make_4_byte_int(buffer);
		if (PLAYER(i).code_size > CHAMP_MAX_SIZE)
		{
			ft_fprintf(2, "Error: File %s has too large code \
(%d bytes > %d bytes)\n", PLAYER(i).file_name, PLAYER(i).code_size, CHAMP_MAX_SIZE);
			return (0);
		}
		if (PLAYER(i).code_size == 0)
		{
			ft_fprintf(2, "Error: File %s is too small to be a champion\n",
													PLAYER(i).file_name);
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
		copy_bytes_to_string(PLAYER(i).comment, buffer,
						*string_size, *string_size += 4);
}

void	make_g_player_code(int amount_bytes, uint8_t buffer[4],
										int i, int *string_size)
{
	if (amount_bytes > BYTES_AFTER_COMMENT + NULL_BYTES)
	{
		if (!PLAYER(i).code)
		{
			PLAYER(i).code = (char *)malloc(sizeof(char) *
									PLAYER(i).code_size);
			ft_bzero(PLAYER(i).code, PLAYER(i).code_size);
		}
		copy_bytes_to_string(PLAYER(i).code, buffer,
					*string_size, *string_size += 4);
	}
}

void	initialize_one_g_player(int i)
{
	PLAYER(i).name = (char *)malloc(sizeof(char) * PROG_NAME_LENGTH);
	PLAYER(i).comment = (char *)malloc(sizeof(char) * COMMENT_LENGTH);
	ft_bzero(PLAYER(i).name, PROG_NAME_LENGTH);
	ft_bzero(PLAYER(i).comment, COMMENT_LENGTH);
	PLAYER(i).identifier = g_vm->plr_nbr[i].identifier;
}
