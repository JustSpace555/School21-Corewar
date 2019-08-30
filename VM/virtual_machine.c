#include "virtual_header.h"

int	virual_machine(int amount_players, char **files_champoins)
{
	g_players = (t_player *)malloc(sizeof(t_player) * amount_players);
	print_hex_data(amount_players, files_champoins);
	return (1);
}
