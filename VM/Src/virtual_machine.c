#include "../Headers/virtual_header.h"

void	initialize_battlefield(void)
{
	int	i;

	i = -1;
	g_battlefield = (t_battlefield *)malloc(sizeof(t_battlefield) * MEM_SIZE);
	while (++i < MEM_SIZE)
	{
		g_battlefield[i].code = 0x0;
		g_battlefield[i].color = '\0';
	}
}

char	choose_color(int i)
{
	if (i == 0)
		return('r');
	else if (i == 1)
		return('y');
	else if (i == 2)
		return('g');
	else if (i == 3)
		return('b');
	else if (i == 4)
		return('p');
	else if (i == 5)
		return('c');
	else if (i == 6)
		return('e');
	else if (i == 7)
		return ('l');
	return ('n');
}

void	virtual_machine(t_vm *vm)
{
	int	diff;
	int	temp;
	int	i;
	int	j;
	int	byte;

	initialize_battlefield();
	diff = MEM_SIZE / vm->amount_players;
	temp = diff;
	i = -1;
	byte = 0;
	while (++i < vm->amount_players)
	{
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
	print_battlefield();
}
