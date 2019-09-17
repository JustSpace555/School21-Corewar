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

void	initialize_g_players(int amount_players)
{
	int	i;

	g_players = (t_player *)malloc(sizeof(t_player) * amount_players);
	i = -1;
	while (++i < amount_players)
	{
		PLAYER(i).start_position = 0;
		PLAYER(i).code = NULL;
		PLAYER(i).code_size = 0;
		PLAYER(i).comment = NULL;
		PLAYER(i).identifier = 0;
		PLAYER(i).name = NULL;
	}
}

void	initialize_battlefield(void)
{
	int	i;

	i = -1;
	g_battlefield = (t_battlefield *)malloc(sizeof(t_battlefield) * MEM_SIZE);
	while (++i < MEM_SIZE)
	{
		g_battlefield[i].code = 0x0;
		g_battlefield[i].color = '\0';
		g_battlefield[i].cursor = false;
	}
}

void	initialize_cursors(int amount_players)
{
	int	i;
	int	j;

	g_cursors = (t_cursor *)malloc(sizeof(t_cursor) * amount_players);
	i = -1;
	while (++i < amount_players)
	{
		CURSOR(i).bytes_to_next_op = 0;
		CURSOR(i).carry = false;
		CURSOR(i).cur_pos = PLAYER(i).start_position;
		CURSOR(i).cycle_exec = -1;
		CURSOR(i).id = PLAYER(i).identifier;
		CURSOR(i).last_alive = 0;
		CURSOR(i).operation_code = 0;
		CURSOR(i).reg[0] = -PLAYER(i).identifier;
		j = 0;
		while (++j < 16)
			CURSOR(i).reg[j] = 0;
	}
	g_cursors_amount = amount_players;
	g_amount_live_operations = 0;
}
