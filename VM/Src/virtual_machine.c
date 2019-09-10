#include "../Headers/virtual_header.h"

void	fill_battlefield(t_vm *vm)
{
	int	i;
	int	j;
	int	diff;
	int	temp;
	int	byte;

	diff = MEM_SIZE / vm->amount_players;
	temp = diff;
	i = -1;
	byte = 0;
	while (++i < vm->amount_players)
	{
		g_players[i].start_position = byte;
		g_battlefield[byte].coach = true;
		j = -1;
		while (++j < PLAYER(i).code_size)
		{
			g_battlefield[byte].code = PLAYER(i).code[j];
			g_battlefield[byte].color = choose_color(i);
			byte++;
		}
		while (byte < MIN(diff, MEM_SIZE))
		{
			g_battlefield[byte].code = 0x0;
			g_battlefield[byte].color = '\0';
			byte++;
		}
		diff += temp;
	}
}

int 	checkup(t_vm *vm, int *lives, int *cycle_to_die)
{
	static int checks = 0;
	static int	unmodifiable = 1;

	if (checks == MAX_CHECKS && unmodifiable)
		*cycle_to_die -= CYCLE_DELTA;
	if (*lives >= NBR_LIVE)
	{
		*cycle_to_die -= CYCLE_DELTA;
		unmodifiable = 0;
		checks = 0;
	}
	(*lives)--;
	return (1);
}

int		check_codage(unsigned char byte, int *args)
{
	int i;
	int j;

	i = 7;
	j = 0;
	while (i >= 3)
	{
		if ((byte >> i & 1) == 1)
		{
			if ((byte >> (i - 1) & 1) == 1)
				args[j] = 3;
			else
				args[j] = 2;
		}
		else
			if ((byte >> (i - 1) & 1) == 1)
				args[j] = 1;
		j += 1;
		i -= 2;
	}
}

unsigned int			ft_atoi_hex(char *str)
{
	unsigned int		res;

	res = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			res = res * 16 + *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			res = res * 16 + *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			res = res * 16 + *str - 'A' + 10;
		else
			return (0);
		str++;
	}
	return (res);
}

int		ld(t_cursor *cursor, int *args)
{
	int	i;
	int pos;

	pos = cursor->cur_pos + 2;
	i = 0;
	printf("%u\n", ft_atoi_hex("A0F000"));
	printf("%i\n", (6 % 0)); //
	if (args[0] == 2)
	{
		//while (pos % cursor->cur_pos <= DIR_SIZE) // протестировать
	}
	else if (args[0] == 3)
	{

	}
//	check_codage(f_byte_of_arguments, args);
	//if g_battlefield[f_byte_of_arguments].code
}

int 	choose_operation(t_vm *vm, t_cursor *cursor, int *args)
{
	if (cursor->operation_code == 1)
	{}
	else if (cursor->operation_code == 2)
		ld(cursor, args);
	else if (cursor->operation_code == 3)
		{}
	else if (cursor->operation_code == 4)
		{}
	else if (cursor->operation_code == 5)
		{}
	else if (cursor->operation_code == 6)
		{}
	else if (cursor->operation_code == 7)
		{}
	else if (cursor->operation_code == 8)
		{}
	else if (cursor->operation_code == 9)
		{}
	else if (cursor->operation_code == 10)
		{}
	else if (cursor->operation_code == 11)
		{}
	else if (cursor->operation_code == 12)
		{}
	else if (cursor->operation_code == 13)
		{}
	else if (cursor->operation_code == 14)
		{}
	else if (cursor->operation_code == 15)
		{}
	else if (cursor->operation_code == 16)
		{}
	return (0);
}

void	execute_operation(t_vm *vm, t_cursor *cursor)
{
	int args[3];

	if (cursor->cycle_exec == 0) // про назначение подумать
	{
		check_codage(g_battlefield[(cursor->cur_pos + 1) % MEM_SIZE].code, args);
		printf("%i\n", args[0]);
		choose_operation(vm, cursor, args);
		//g_battlefield[byte].code = 0x0;
		// назначить cycle_exec в функции
	}
	else
	{
		cursor->cycle_exec--;
	}
}

void	virtual_machine(t_vm *vm)
{
	int cycle;
	int cycle_to_die;

	cycle = -1;
	cycle_to_die = CYCLE_TO_DIE;
	initialize_battlefield();
	fill_battlefield(vm);
	initialize_cursor(vm->amount_players);
	print_battlefield();
	while (cycle_to_die > 0)
	{
		int lives = 0;

		if (cycle == cycle_to_die)  // сделать проверку
			checkup(vm, &lives, &cycle_to_die);

		int i = -1;
		int dead = 0;
		while (++i < vm->amount_players)
		{
			if (g_cursor[i].last_alive / cycle_to_die == 0)
				execute_operation(vm, &g_cursor[i]);
			else
				dead++; // исправить
		}
		cycle++;
		cycle_to_die = 0; // удалить потом
	}
}
