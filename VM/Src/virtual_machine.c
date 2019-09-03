#include "../Headers/virtual_header.h"

void	virtual_machine(int amount_players, char **files_champions)
{
	unsigned char	arena[MEM_SIZE];

	if (players_parser(amount_players, files_champions) == -1)
		return ;
}
