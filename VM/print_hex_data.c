#include "virtual_header.h"

void	print_zero(char *color, uint8_t buffer)
{
	if (buffer / 16 < 1)
		printf("%s"NORMAL, ft_strjoin(color, "0"));
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
