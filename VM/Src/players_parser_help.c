#include "../Headers/virtual_header.h"

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

void		copy_bytes_to_string(char **str, u_int8_t buffer[4])
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

void	print_zero(char *color, uint8_t buffer)
{
	if (buffer / 16 < 1)
		ft_printf("%s"NORMAL, ft_strjoin(color, "0"));
}

void	free_g_players(int amount_players)
{
	int	i;

	i = -1;
	while (++i < amount_players)
	{
		free(PLAYER(i).code);
		free(PLAYER(i).comment);
		free(PLAYER(i).name);
	}
	free(g_players);
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
