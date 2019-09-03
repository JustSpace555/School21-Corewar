#include "../Headers/virtual_header.h"

int 	*init_int_array(int size, int nbr)
{
	int *array;
	int i;

	i = -1;
	array = (int*)malloc(sizeof(int) * size);

	while (++i < size)
		array[i] = nbr;
	return (array);
}

void	initialize_vm(t_vm *vm)
{
	int i;

	i = -1;
	vm->dump = -1;
	vm->vis = -1;
	vm->order_idtfrs = init_int_array(MAX_PLAYERS, 0);
	vm->plr_nbr = malloc(sizeof(t_plr_nbr) * MAX_PLAYERS);
	vm->amount_players = 0;
	while (++i < MAX_PLAYERS)
	{
		vm->plr_nbr[i].index_file = 0;
		vm->plr_nbr[i].identifier = 0;
	}
}
