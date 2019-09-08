#include "../Headers/virtual_header.h"

void	show_bin_int(unsigned int i)
{
	int j;

	j = 0;
	while (++j <= 32)
	{
		if (i & 0x80000000)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i = i << 1;
		if (j % 8 == 0 && j != 0)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void	show_bin_char(unsigned char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 0x80)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		c = c << 1;
	}
	write(1, "\n", 1);
}

void	print_players(int amount_players)
{
	int	i;
	int	j;

	i = -1;
	while (++i < amount_players)
	{
		j = 0;
		ft_printf("Player number = %d\n", PLAYER(i).identifier);
		ft_printf("Name = %s\n", PLAYER(i).name);
		ft_printf("Comment = %s\n", PLAYER(i).comment);
		ft_printf("Code size = %d\n", PLAYER(i).code_size);
		printf("Code:\n");
		while (j < PLAYER(i).code_size)
		{
			if (j % 8 == 0 && j != 0)
				printf("\n");
			printf("%02hhx ", PLAYER(i).code[j]);
			j += 1;
		}
		ft_printf("\n\n");
	}
}

void	print_hex_data(char *file)
{
	int	fd;
	int		i = 0;
	uint8_t	buffer[4];
	int		count = 0;

	fd = open(file, O_RDONLY);
	ft_printf("Filename = %s\n", file);
	while (read(fd, &buffer, 4))
	{
	for (int i = 0; i < 4; i++)
		{
			if (count < 4 || (count >= PROG_NAME_LENGTH + 12 && count <
					COMMENT_LENGTH + PROG_NAME_LENGTH + 12))
				ft_printf(RED"%02hhx "NORMAL, buffer[i]);
			else if (count >= 4 && count < PROG_NAME_LENGTH + 4)
				ft_printf(YELLOW"%02hhx "NORMAL, buffer[i]);
			else if ((count >= PROG_NAME_LENGTH + 4 && count <
						PROG_NAME_LENGTH + 8) || (count >= COMMENT_LENGTH
							+ 12 + PROG_NAME_LENGTH && count < COMMENT_LENGTH
								+ 16 + PROG_NAME_LENGTH))
				ft_printf(BLACK"%02hhx "NORMAL, buffer[i]);
			else if (count >= COMMENT_LENGTH + 16 + PROG_NAME_LENGTH
					|| (count >= PROG_NAME_LENGTH + 8 && count <
						PROG_NAME_LENGTH + 12))
				ft_printf(CYAN"%02hhx "NORMAL, buffer[i]);
			count++;
		}
		ft_printf("%d\n", count);
	}
	close(fd);
}

void	print_battlefield(void)
{
	int	print_bytes;
	int	c;

	print_bytes = 0;
	c = -1;
	while (++c < MEM_SIZE)
	{
		if (print_bytes % CODE_PER_LINE == 0)
			ft_printf("\n0x%04x: ", print_bytes);
		if (g_battlefield[c].color == 'r')
		{
			if (g_battlefield[c].cursor)
				ft_printf(RED_BG"%{black}02hhx ", g_battlefield[c].code);
			else
				ft_printf("%{red}02hhx ", g_battlefield[c].code);
		}
		else if (g_battlefield[c].color == 'y')
		{
			if (g_battlefield[c].cursor)
				ft_printf(YELLOW_BG"%{black}02hhx ", g_battlefield[c].code);
			else
				ft_printf("%{yellow}02hhx ", g_battlefield[c].code);
		}
		else if (g_battlefield[c].color == 'g')
		{
			if (g_battlefield[c].cursor)
				ft_printf(GREEN_BG"%{black}02hhx ", g_battlefield[c].code);
			else
				ft_printf("%{green}02hhx ", g_battlefield[c].code);
		}
		else if (g_battlefield[c].color == 'b')
		{
			if (g_battlefield[c].cursor)
				ft_printf(BLUE_BG"%{black}02hhx ", g_battlefield[c].code);
			else
				ft_printf("%{blue}02hhx ", g_battlefield[c].code);
		}
		else if (g_battlefield[c].color == 'p')
		{
			if (g_battlefield[c].cursor)
				ft_printf(PURPLE_BG"%{black}02hhx ", g_battlefield[c].code);
			else
				ft_printf("%{purple}02hhx ", g_battlefield[c].code);
		}
		else if (g_battlefield[c].color == 'c')
		{
			if (g_battlefield[c].cursor)
				ft_printf(CYAN_BG"%{black}02hhx ", g_battlefield[c].code);
			else
				ft_printf("%{cyan}02hhx ", g_battlefield[c].code);
		}
		else if (g_battlefield[c].color == 'l')
		{
			if (g_battlefield[c].cursor)
				ft_printf(BLACK_BG"%{black}02hhx ", g_battlefield[c].code);
			else
				ft_printf("%{black}02hhx ", g_battlefield[c].code);
		}
		else if (g_battlefield[c].color == 'e')
		{
			if (g_battlefield[c].cursor)
				ft_printf(WHITE_BG"%{black}02hhx ", g_battlefield[c].code);
			else
				ft_printf("%{grey}02hhx ", g_battlefield[c].code);
		}
		else
			ft_printf("%02hhx ", g_battlefield[c].code);
		print_bytes++;
	}
	ft_printf("\n");
}
