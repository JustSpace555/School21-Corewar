/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_parser_help_pt1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:35 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 15:40:32 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

int		make_4_byte_int(u_int8_t buffer[4])
{
	int temp;

	temp = 0x0;
	temp |= buffer[0];
	temp = temp << 8;
	temp |= buffer[1];
	temp = temp << 8;
	temp |= buffer[2];
	temp = temp << 8;
	temp |= buffer[3];
	return (temp);
}

void	copy_bytes_to_string(char *str, u_int8_t buffer[4],
							int amount_of_bytes, int code_size)
{
	int	i;

	i = -1;
	while (++i < 4 && amount_of_bytes + i < code_size)
		str[amount_of_bytes + i] = buffer[i];
}

int		check_for_header(u_int8_t buffer[4])
{
	if (make_4_byte_int(buffer) != COREWAR_EXEC_MAGIC)
		return (0);
	return (1);
}

int		get_code_size(u_int8_t buffer[4])
{
	int	temp;

	temp = make_4_byte_int(buffer);
	if (temp > CHAMP_MAX_SIZE)
		return (-1);
	return (temp);
}

int		if_header_bytes(int amount_bytes, uint8_t buffer[4])
{
	if (amount_bytes == BYTES_AFTER_HEADER)
		if (!check_for_header(buffer))
		{
			ft_fprintf(2, "Virtual Machine error: \
No magic header in file\n");
			return (0);
		}
	return (1);
}
