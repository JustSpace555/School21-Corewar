#include "../Headers/virtual_header.h"

int		players_parser(char **files_champions)
{
	int			i;
	int			fd;
	int			amount_bytes;
	char		*name;
	char		*comment;
	int			temp;
	int			amount_memory;
	u_int8_t	buffer[4];

	initialize_g_players();
	i = -1;
	amount_memory = 0;
	while (++i < g_vm->amount_players)
	{
		amount_bytes = 0;
		name = (char *)malloc(sizeof(char) * PROG_NAME_LENGTH);
		comment = (char *)malloc(sizeof(char) * COMMENT_LENGTH);
		ft_bzero(name, PROG_NAME_LENGTH);
		ft_bzero(comment, COMMENT_LENGTH);
		fd = open(files_champions[i], O_RDONLY);
		PLAYER(i).identifier = g_vm->plr_nbr[i].identifier;
		temp = 0;
		while (read(fd, buffer, 4))
		{
			amount_bytes += 4;
			if (amount_bytes == BYTES_AFTER_HEADER)
				if (check_for_header(buffer) == -1)
				{
					ft_printf("Virtual Machine error: No magic header in file\n");
					return (-1);
				}
			if (amount_bytes > BYTES_AFTER_HEADER && amount_bytes <= BYTES_AFTER_NAME)
			{
				copy_bytes_to_string(&name, buffer, temp, temp + 4);
				temp += 4;
			}
			if (amount_bytes == BYTES_AFTER_NAME)
			{
				PLAYER(i).name = name;
				name = NULL;
				free(name);
				temp = 0;
			}
			if (amount_bytes > BYTES_AFTER_NAME + NULL_BYTES && amount_bytes <= BYTES_AFTER_CODE_SIZE)
			{
				PLAYER(i).code_size = make_4_byte_int(buffer);
				if (PLAYER(i).code_size > CHAMP_MAX_SIZE)
				{
					ft_printf("Error: %s's players size bigger than permitted (%d bytes > %d bytes)\n", PLAYER(i).name, PLAYER(i).code_size, CHAMP_MAX_SIZE);
					return (-1);
				}
				amount_memory += PLAYER(i).code_size;
				if (amount_memory > MEM_SIZE)
				{
					printf("Virual machine error: players mem size bigger than permitted (%d > %d)\n", amount_memory, MEM_SIZE);
					return(-1);
				}
			}
			if (amount_bytes > BYTES_AFTER_CODE_SIZE && amount_bytes <= BYTES_AFTER_COMMENT)
			{
				copy_bytes_to_string(&comment, buffer, temp, temp + 4);
				temp += 4;
			}
			if (amount_bytes == BYTES_AFTER_COMMENT)
			{
				PLAYER(i).comment = comment;
				comment = NULL;
				free(comment);
				temp = 0;
			}
			if (amount_bytes > BYTES_AFTER_COMMENT + NULL_BYTES)
			{
				if (!PLAYER(i).code)
				{
					PLAYER(i).code = (char *)malloc(sizeof(char) * PLAYER(i).code_size);
					ft_bzero(PLAYER(i).code, PLAYER(i).code_size);
				}
				copy_bytes_to_string(&PLAYER(i).code, buffer, temp, PLAYER(i).code_size);
				temp += 4;
			}
		}
		close(fd);
	}
	return (1);
}
