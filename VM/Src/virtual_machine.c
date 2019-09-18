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
	return (0);
}

unsigned long	ft_atoi_hex(char *str)
{
	unsigned long	res;

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

unsigned long	read_byte(unsigned char *byte, int bytes_offset)
{
	unsigned long	res;
	int 			offset;

	offset = (bytes_offset * 8);
	res = 0;
	res += ((res >> offset) | *byte) << offset;
	return (res);
}

unsigned long	read_argument(int first_byte_i, int size_bytes)
{
	unsigned long	res;
	int i;
	int byte;

	byte = first_byte_i % MEM_SIZE;
	i = 0;
	res = 0;
	while (++i <= size_bytes)
	{
		res += read_byte(&g_battlefield[byte].code, i - 1);
		byte = (byte + 1) % MEM_SIZE;
	}
	//printf("Число: %lu\n", res);
	return (res);
}

int 	add(t_cursor *cursor)
{
	int pos;
	int i_reg1;
	int i_reg2;
	int i_reg3;

	cursor->bytes_to_next_op += 1; // за codage
	pos = (cursor->cur_pos + 2) % MEM_SIZE;
	i_reg1 = read_argument(pos, 1);
	i_reg2 = read_argument((pos + 1) % MEM_SIZE, 1);
	i_reg3 = read_argument((pos + 2) % MEM_SIZE, 1)
	cursor->reg[i_reg3] = cursor->reg[i_reg1] + cursor->reg[i_reg2];
	cursor->carry = (cursor->reg[i_reg3] == 0) ? 1 : 0;
	cursor->bytes_to_next_op += 3; // за регистры
}

int		ld(t_cursor *cursor, int *args)
{
	int	i;
	int pos;
	unsigned int	value;
	int 			i_reg;
	int 			relative_address;

	cursor->bytes_to_next_op += 1; // за codage
	pos = (cursor->cur_pos + 2) % MEM_SIZE;
	i = 0;

	if (args[0] == 2)
	{
		value = read_argument(pos, DIR_SIZE);
		cursor->carry = (value == 0) ? 1 : 0; // убедиться, что везде есть
		i_reg = read_argument((pos + 4) % MEM_SIZE, 1);
		if (i_reg < 1 | i_reg > REG_SIZE)
			return (1); // просто закончить
		cursor->reg[i_reg] = value;
		printf("value: %u will writed at %i-th register\n", value, i_reg);
		cursor->bytes_to_next_op += DIR_SIZE;  // подсчет возиожно изменить
	}
	else if (args[0] == 3) // протестировать
	{
		relative_address = read_argument(pos, IND_SIZE) % IDX_MOD;
		relative_address = (cursor->cur_pos + relative_address) % MEM_SIZE;
		value = read_argument(relative_address, DIR_SIZE);
		i_reg = read_argument((pos + 2) % MEM_SIZE, 1);
		if (i_reg < 1 | i_reg > REG_SIZE)
			return (1); // просто закончить
		cursor->reg[i_reg] = value;
		cursor->bytes_to_next_op += IND_SIZE;
	}
	cursor->bytes_to_next_op += 1; // + 1 byte register
	return (0);
}

int 	execute_operation(t_vm *vm, t_cursor *cursor, int *args)
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

void	move_cursor(t_cursor *cursor)
{
	g_battlefield[cursor->cur_pos].coach = 0;
	cursor->cur_pos += cursor->bytes_to_next_op;
	g_battlefield[cursor->cur_pos].coach = 1;
}

int 	set_cycle_to_exec(int nbr_op)
{
	if (nbr_op == 1)
		return (10);
	else if(nbr_op == 2)
		return (5);
	else if(nbr_op == 3)
		return (5);
	else if(nbr_op == 4)
		return (10);
	else if(nbr_op == 5)
		return (10);
	else if(nbr_op == 6)
		return (6);
	else if(nbr_op == 7)
		return (6);
	else if(nbr_op == 8)
		return (6);
	else if(nbr_op == 9)
		return (20);
	else if(nbr_op == 10)
		return (25);
	else if(nbr_op == 11)
		return (25);
	else if(nbr_op == 12)
		return (800);
	else if(nbr_op == 13)
		return (10);
	else if(nbr_op == 14)
		return (50);
	else if(nbr_op == 15)
		return (1000);
	else if(nbr_op == 16)
		return (2);
	return (-1);
}

void	check_cursor(t_vm *vm, t_cursor *cursor)
{
	int args[3];

	if (cursor->cycle_exec == 0)
	{

		cursor->operation_code = g_battlefield[cursor->cur_pos].code;
		if (cursor->operation_code >= 1 && cursor->operation_code <= 16)
			cursor->cycle_exec 	= set_cycle_to_exec(cursor->operation_code);
		cursor->bytes_to_next_op = 1;
	}
	cursor->cycle_exec = (cursor->cycle_exec > 0) ? cursor->cycle_exec-- : 0;
	if (cursor->cycle_exec == 0)
	{
		if (cursor->operation_code < 1 || cursor->operation_code > 16)
			move_cursor(cursor);
		else
		{
			check_codage(g_battlefield[(cursor->cur_pos + 1) % MEM_SIZE].code, args);
			execute_operation(vm, cursor, args);
			move_cursor(cursor);
		}
	}
}

void	virtual_machine(t_vm *vm)
{
	int cycle;
	int cycle_to_die;
	int i;

	cycle = 0;
	cycle_to_die = CYCLE_TO_DIE;
	initialize_battlefield();
	fill_battlefield(vm);
	initialize_cursor(vm->amount_players);
	print_battlefield(); // удалить
	while (cycle_to_die > 0)
	{
		int lives = 0;
		if (cycle == cycle_to_die)  // сделать проверку
			checkup(vm, &lives, &cycle_to_die);
		i = -1;
		while (++i < vm->amount_players)
		{
			if (g_cursor[i].last_alive != -1 && g_cursor[i].last_alive / cycle_to_die == 0)
				check_cursor(vm, &g_cursor[i]);
			else
				g_cursor[i].last_alive = -1;
		}
		cycle++;
		cycle_to_die = 0; // удалить потом
	}
	print_battlefield();
}
