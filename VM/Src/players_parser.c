#include "../Headers/virtual_header.h"

int		if_header_bytes(int amount_bytes, uint8_t buffer[4])
{
	if (amount_bytes == BYTES_AFTER_HEADER)
		if (!check_for_header(buffer))
		{
			ft_printf("Virtual Machine error: \
						No magic header in file\n");
			return (0);
		}
	return (1);
}

void	make_g_player_name(int amount_bytes, uint8_t buffer[4], int i, int *string_size)
{
	if (amount_bytes > BYTES_AFTER_HEADER &&
			amount_bytes <= BYTES_AFTER_NAME)
		copy_bytes_to_string(PLAYER(i).name, buffer, *string_size, *string_size += 4);
}

int		make_g_player_size(int amount_bytes, uint8_t buffer[4], int i)
{
	if (amount_bytes > BYTES_AFTER_NAME + NULL_BYTES &&
						amount_bytes <= BYTES_AFTER_CODE_SIZE)
	{
		PLAYER(i).code_size = make_4_byte_int(buffer);
		if (PLAYER(i).code_size > CHAMP_MAX_SIZE)
		{
			ft_printf("Error: %s's players size bigger than permitted \
							(%d bytes > %d bytes)\n", PLAYER(i).name,
								PLAYER(i).code_size, CHAMP_MAX_SIZE);
			return (0);
		}
	}
	return (1);
}

void	make_g_player_comment(int amount_bytes, uint8_t buffer[4], int i, int *string_size)
{
	if (amount_bytes > BYTES_AFTER_CODE_SIZE &&
			amount_bytes <= BYTES_AFTER_COMMENT)
		copy_bytes_to_string(PLAYER(i).comment, buffer, *string_size, *string_size += 4);
}

void	make_g_player_code(int amount_bytes, int i, uint8_t buffer[4], int *string_size)
{
	if (amount_bytes > BYTES_AFTER_COMMENT + NULL_BYTES)
	{
		if (!PLAYER(i).code)
		{
			PLAYER(i).code = (char *)malloc(sizeof(char) *
									PLAYER(i).code_size);
			ft_bzero(PLAYER(i).code, PLAYER(i).code_size);
		}
		copy_bytes_to_string(PLAYER(i).code, buffer, *string_size, *string_size += 4);
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

int		check_for_ovetflow(void)
{
	int	i;
	int	amount_memory;

	i = -1;
	amount_memory = 0;
	while (++i < g_vm->amount_players)
		amount_memory += PLAYER(i).code_size;
	if (amount_memory > MEM_SIZE)
	{
		printf("Virual machine error: players mem size bigger \
			than permitted (%d > %d)\n", amount_memory, MEM_SIZE);
		return (0);
	}
	return (1);
}

int		players_parser(char **files_champions)
{
	int			i;
	int			fd;
	int			amount_bytes;
	int			amount_memory;
	u_int8_t	buffer[4];
	int			string_size;

	initialize_g_players();
	i = -1;
	amount_memory = 0;
	while (++i < g_vm->amount_players)
	{
		amount_bytes = 0;
		fd = open(files_champions[i], O_RDONLY);
		initialize_one_g_player(i);
		while (read(fd, buffer, 4))
		{
			amount_bytes += 4;
			zeroing_string_size(&string_size, amount_bytes);
			if (!if_header_bytes(amount_bytes, buffer))
				return(0);
			make_g_player_name(amount_bytes, buffer, i, &string_size);
			if (!make_g_player_size(amount_bytes, buffer, i))
				return(0);
			make_g_player_comment(amount_memory, buffer, i, &string_size);
			make_g_player_code(amount_bytes, i, buffer, &string_size);
		}
		close(fd);
	}
	if (!check_for_ovetflow())
		return (0);
	return (1);
}
