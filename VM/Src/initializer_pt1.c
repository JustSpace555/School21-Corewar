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

void	initialize_vm(void)
{
	int i;

	i = -1;
	g_vm = (t_vm *)malloc(sizeof(t_vm));
	g_vm->dump = -1;
	g_vm->vis = -1;
	g_vm->ver = -1;
	g_vm->last_live_player = 0;
	g_vm->order_idtfrs = init_int_array(MAX_PLAYERS, 0);
	g_vm->plr_nbr = (t_plr_nbr *)malloc(sizeof(t_plr_nbr) * MAX_PLAYERS);
	g_vm->amount_players = 0;
	while (++i < MAX_PLAYERS)
	{
		g_vm->plr_nbr[i].index_file = 0;
		g_vm->plr_nbr[i].identifier = 0;
	}
}

void	initialize_g_players(void)
{
	int	i;

	g_players = (t_player *)malloc(sizeof(t_player) * g_vm->amount_players);
	i = -1;
	while (++i < g_vm->amount_players)
	{
		PLAYER(i).start_position = 0;
		PLAYER(i).code = NULL;
		PLAYER(i).code_size = 0;
		PLAYER(i).comment = NULL;
		PLAYER(i).identifier = 0;
		PLAYER(i).name = NULL;
		PLAYER(i).last_alive = 0;
		PLAYER(i).nbr_live = 0;
		PLAYER(i).amount_cursors = 1;
		PLAYER(i).aff_out = NULL;
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
		g_battlefield[i].color_b = 0;
		g_battlefield[i].color_g = 0;
		g_battlefield[i].color_r = 0;
		g_battlefield[i].write_cycles = 0;
		g_battlefield[i].cursor = false;
	}
}

void	initialize_cursors()
{
	int	i;
	int	j;
	int	plr_id;

	g_cursors = (t_cursor *)malloc(sizeof(t_cursor) * g_vm->amount_players);
	i = -1;
	plr_id = g_vm->amount_players;
	while (++i < g_vm->amount_players)
	{
		CURSOR(i).bytes_to_next_op = 0;
		CURSOR(i).carry = false;
		CURSOR(i).cur_pos = PLAYER(--plr_id).start_position;
		CURSOR(i).cycle_exec = 0;
		CURSOR(i).player_id = PLAYER(plr_id).identifier;
		CURSOR(i).cursror_id = PLAYER(plr_id).identifier;
		CURSOR(i).last_alive = 0;
		CURSOR(i).operation_code = 0;
		CURSOR(i).reg[0] = -PLAYER(plr_id).identifier;
		CURSOR(i).color = g_battlefield[CURSOR(i).cur_pos].color;
		j = 0;
		while (++j < 16)
			CURSOR(i).reg[j] = 0;
	}
	g_cursors_amount = g_vm->amount_players;
	g_amount_live_operations = 0;
}
