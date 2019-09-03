#include "../Headers/virtual_header.h"

int		free_players(int amount_players)
{
	int	i;

	i = -1;
	while (++i < amount_players)
	{
		if (g_players[i].code)
			free(g_players[i].code);
		if (g_players[i].comment)
			free(g_players[i].comment);
		if (g_players[i].name)
			free(g_players[i].name);
	}
	free(g_players);
	return (-1);
}

void	make_new_g_players(int amount_players)
{
	int	i;

	g_players = (t_player *)malloc(sizeof(t_player) * amount_players);
	i = -1;
	while (++i < amount_players)
	{
		g_players[i].code = NULL;
		g_players[i].code_size = 0;
		g_players[i].comment = NULL;
		g_players[i].identifier = 0;
		g_players[i].name = NULL;
	}
}

int		players_parser(int amount_players, char **files_champions, t_vm vm)
{
	int			i;
	int			fd;
	int			amount_bytes;
	char		*name;
	char		*comment;
	u_int8_t	buffer[4];

	make_new_g_players(amount_players);
	i = -1;
	while (++i < amount_players)
	{
		amount_bytes = 0;
		name = (char *)malloc(sizeof(char) * PROG_NAME_LENGTH);
		comment = (char *)malloc(sizeof(char) * COMMENT_LENGTH);
		ft_bzero(name, PROG_NAME_LENGTH);
		ft_bzero(comment, COMMENT_LENGTH);
		fd = open(files_champions[i], O_RDONLY);
		PLAYER(i).identifier = vm.plr_nbr[i].identifier;
		while (read(fd, buffer, 4))
		{
			amount_bytes += 4;
			if (amount_bytes == BYTES_AFTER_HEADER)
				if (check_for_header(buffer) == -1)
				{
					ft_printf("Virtual Machine error: No magic header in file\n");
					return (free_players(amount_players));
				}
			if (amount_bytes > BYTES_AFTER_HEADER && amount_bytes <= BYTES_AFTER_NAME)
				copy_bytes_to_string(&name, buffer);
			if (amount_bytes == BYTES_AFTER_NAME)
			{
				PLAYER(i).name = name;
				name = NULL;
				free(name);
			}
			if (amount_bytes > BYTES_AFTER_NAME + NULL_BYTES && amount_bytes <= BYTES_AFTER_CODE_SIZE)
			{
				PLAYER(i).code_size = get_code_size(buffer);
				if (PLAYER(i).code_size == -1)
				{
					ft_printf("Error: %s size bigger than max (%d)\n", PLAYER(i).name, CHAMP_MAX_SIZE);
					return (free_players(amount_players));
				}
				PLAYER(i).code = (char *)malloc(sizeof(char) * PLAYER(i).code_size);
				ft_bzero(PLAYER(i).code, PLAYER(i).code_size);
			}
			if (amount_bytes > BYTES_AFTER_CODE_SIZE && amount_bytes <= BYTES_AFTER_COMMENT)
				copy_bytes_to_string(&comment, buffer);
			if (amount_bytes == BYTES_AFTER_COMMENT)
			{
				PLAYER(i).comment = comment;
				comment = NULL;
				free(comment);
			}
			if (amount_bytes > BYTES_AFTER_COMMENT + NULL_BYTES)
				copy_bytes_to_string(&PLAYER(i).code, buffer);
		}
		close(fd);
	}
	print_players(amount_players);
	return (1);
}
