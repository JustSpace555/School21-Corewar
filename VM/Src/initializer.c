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
		g_players[i].start_position = 0;
		g_players[i].code = NULL;
		g_players[i].code_size = 0;
		g_players[i].comment = NULL;
		g_players[i].identifier = 0;
		g_players[i].name = NULL;
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
		g_battlefield[i].coach = false;
	}
}

void	initialize_cursor(int amount_players)
{
	int	i;
	int	j;

	g_cursor = (t_cursor *)malloc(sizeof(t_cursor) * amount_players);
	i = amount_players;
	while (--i >= 0)
	{
		g_cursor[i].bytes_to_next_op = 0;
		g_cursor[i].carry = false;
		g_cursor[i].cur_pos = PLAYER(i).start_position;
		g_cursor[i].cycle_exec = 0;
		g_cursor[i].id = PLAYER(i).identifier;
		g_cursor[i].last_alive = 0;
		g_cursor[i].operation_code = 0;
		g_cursor[i].reg[0] = -PLAYER(i).identifier;
		j = 0;
		while (++j < 16)
			g_cursor[i].reg[j] = 1;
	}
}
