#include "../Headers/virtual_header.h"

int 	ft_is_strdigit(char *str)
{
	if (!str || *str == '\0')
		return (-1);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
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
