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
		printf("Player number = %d\n", PLAYER(i).identifier);
		printf("Name = %s\n", PLAYER(i).name);
		printf("Comment = %s\n", PLAYER(i).comment);
		printf("Code size = %d\n", PLAYER(i).code_size);
		printf("Code:\n");
		while (j < PLAYER(i).code_size)
		{
			if (j % 8 == 0 && j != 0)
				printf("\n");
			printf("%x ", PLAYER(i).code[j]);
			j += 4;
		}
		printf("\n\n");
	}
}

void	print_hex_data(char *file)
{
	int	fd;
	int		i = 0;
	uint8_t	buffer[4];
	int		count = 0;

	fd = open(file, O_RDONLY);
	printf("Filename = %s\n", file);
	while (read(fd, &buffer, 4))
	{
	for (int i = 0; i < 4; i++)
		{
			if (count < 4 || (count >= PROG_NAME_LENGTH + 12 && count < COMMENT_LENGTH + PROG_NAME_LENGTH + 12))
			{
				print_zero(RED, buffer[i]);
				printf(RED"%x "NORMAL, buffer[i]);
			}
			else if (count >= 4 && count < PROG_NAME_LENGTH + 4)
			{
				print_zero(YELLOW, buffer[i]);
				printf(YELLOW"%x "NORMAL, buffer[i]);
			}
			else if ((count >= PROG_NAME_LENGTH + 4 && count < PROG_NAME_LENGTH + 8) || (count >= COMMENT_LENGTH + 12 + PROG_NAME_LENGTH && count < COMMENT_LENGTH + 16 + PROG_NAME_LENGTH))
			{
				print_zero(BLACK, buffer[i]);
				printf(BLACK"%x "NORMAL, buffer[i]);
			}
			else if (count >= COMMENT_LENGTH + 16 + PROG_NAME_LENGTH || (count >= PROG_NAME_LENGTH + 8 && count < PROG_NAME_LENGTH + 12))
			{
				print_zero(CYAN, buffer[i]);
				printf(CYAN"%x "NORMAL, buffer[i]);
			}
			count++;
		}
		printf("%d\n", count);
	}
	close(fd);
}
