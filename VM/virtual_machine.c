#include "virtual_header.h"

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

int		make_4_byte_int(u_int8_t buffer[4])
{
	int temp;

	temp = 0x0;
	temp = temp | buffer[0];
	temp = temp << 8;
	temp = temp | buffer[1];
	temp = temp << 8;
	temp = temp | buffer[2];
	temp = temp << 8;
	temp = temp | buffer[3];
	return (temp);
}

void	copy_bytes_to_string(char **str, u_int8_t buffer[4])
{
	char	*temp;
	int		len;

	if (make_4_byte_int(buffer) == 0)
		return ;
	len = ft_strlen(*str);
	for (int i = 0; i < 4; i++)
		(*str)[len + i] = buffer[i];
}

int		check_for_header(u_int8_t buffer[4])
{
	if (make_4_byte_int(buffer) != COREWAR_EXEC_MAGIC)
		return (-1);
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

int		virual_machine(int amount_players, char **files_champoins)
{
	int			i;
	int			fd;
	int			amount_bytes;
	char		*name;
	char		*comment;
	u_int8_t	buffer[4];

	g_players = (t_player *)malloc(sizeof(t_player) * amount_players);
	i = 0;
	while (++i < amount_players)
	{
		amount_bytes = 0;
		name = (char *)malloc(sizeof(char) * PROG_NAME_LENGTH);
		comment = (char *)malloc(sizeof(char) * COMMENT_LENGTH);
		ft_bzero(name, PROG_NAME_LENGTH);
		ft_bzero(comment, COMMENT_LENGTH);
		fd = open(files_champoins[i], O_RDONLY);
		g_players[i].identifier = i;
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
				copy_bytes_to_string(&name, buffer);
			if (amount_bytes == BYTES_AFTER_NAME)
			{
				g_players[i].name = name;
				free(name);
			}
			if (amount_bytes > BYTES_AFTER_NAME + NULL_BYTES && amount_bytes <= BYTES_AFTER_CODE_SIZE)
			{
				g_players[i].code_size = get_code_size(buffer);
				if (g_players[i].code_size == -1)
				{
					ft_printf("%s size bigger than max (%d)\n", g_players[i].name, CHAMP_MAX_SIZE);
					return (-1);
				}
			}
			if (amount_bytes > BYTES_AFTER_CODE_SIZE && amount_bytes <= BYTES_AFTER_COMMENT)
				copy_bytes_to_string(&comment, buffer);
		}
		close(fd);
	}
	return (1);
}
