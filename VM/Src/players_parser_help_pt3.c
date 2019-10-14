/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_parser_help_pt3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:42 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 13:05:42 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

void	zeroing_string_size(int *string_size, int amount_bytes)
{
	if ((amount_bytes > BYTES_AFTER_NAME &&
		amount_bytes <= BYTES_AFTER_NAME + NULL_BYTES) ||
		(amount_bytes > BYTES_AFTER_CODE_SIZE &&
		amount_bytes <= BYTES_AFTER_CODE_SIZE + NULL_BYTES) ||
		(amount_bytes > BYTES_AFTER_COMMENT &&
		amount_bytes <= BYTES_AFTER_COMMENT + NULL_BYTES) ||
		amount_bytes == BYTES_AFTER_HEADER)
		*string_size = 0;
}

int		check_for_overflow(void)
{
	int	i;
	int	amount_memory;

	i = -1;
	amount_memory = 0;
	while (++i < g_vm->amount_players)
		amount_memory += PLAYER(i).code_size;
	if (amount_memory > MEM_SIZE)
	{
		ft_fprintf(2, \
		"Virual machine error: players mem size \
bigger than permitted (%d > %d)\n", amount_memory, MEM_SIZE);
		return (-1);
	}
	return (1);
}

int		check_fd(int *fd, char *champion_file)
{
	*fd = open(champion_file, O_RDONLY);
	if (*fd == -1)
	{
		ft_fprintf(2, "Failed to open file: %s\n", champion_file);
		return (-1);
	}
	return (1);
}
