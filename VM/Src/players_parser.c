#include "../Headers/virtual_header.h"

int		if_header_bytes(int amount_bytes, uint8_t buffer[4])
{
	if (amount_bytes == BYTES_AFTER_HEADER)
		if (check_for_header(buffer) == -1)
		{
			ft_printf("Virtual Machine error: \
						No magic header in file\n");
			return (0);
		}
	return (1);
}

void	make_g_player_name(int amount_bytes, uint8_t buffer[4], int i)
{
	char	*temp;
	if (amount_bytes > BYTES_AFTER_HEADER &&
			amount_bytes <= BYTES_AFTER_NAME)
	{
		temp = PLAYER(i).name;
		PLAYER(i).name = ft_strjoin(PLAYER(i).name, (char *)buffer);
		free(temp);
	}
}

int		make_g_player_size(int *amount_memory, int amount_bytes, uint8_t buffer[4], int i)
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
		*amount_memory += PLAYER(i).code_size;
		if (*amount_memory > MEM_SIZE)
		{
			printf("Virual machine error: players mem size bigger \
				than permitted (%d > %d)\n", *amount_memory, MEM_SIZE);
			return (0);
		}
	}
	return (1);
}

void	make_g_player_comment(int amount_bytes, uint8_t buffer[4], int i)
{
	char	*temp;

	if (amount_bytes > BYTES_AFTER_CODE_SIZE &&
			amount_bytes <= BYTES_AFTER_COMMENT)
	{
		temp = PLAYER(i).comment;
		PLAYER(i).comment = ft_strjoin(PLAYER(i).comment, (char *)buffer);
		free(temp);
	}
}

void	make_g_player_code(int amount_bytes, int i, uint8_t buffer[4])
{
	char	*temp;

	if (amount_bytes > BYTES_AFTER_COMMENT + NULL_BYTES)
	{
		if (!PLAYER(i).code)
		{
			PLAYER(i).code = (char *)malloc(sizeof(char) *
									PLAYER(i).code_size);
			ft_bzero(PLAYER(i).code, PLAYER(i).code_size);
		}
		temp = PLAYER(i).code;
		PLAYER(i).code = ft_strjoin(PLAYER(i).code, (char *)buffer);
		free(temp);
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

int		players_parser(char **files_champions)
{
	int			i;
	int			fd;
	int			amount_bytes;
	int			amount_memory;
	u_int8_t	buffer[4];

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
			if (!if_header_bytes(amount_bytes, buffer))
				return(0);
			make_g_player_name(amount_bytes, buffer, i);
			if (!make_g_player_size(&amount_memory, amount_bytes, buffer, i))
				return(0);
			make_g_player_comment(amount_memory, buffer, i);
			make_g_player_code(amount_bytes, i, buffer);
		}
		close(fd);
	}
	return (1);
}
