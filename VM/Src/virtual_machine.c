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

void	virtual_machine(t_vm *vm)
{
	int	diff;
	int	i;
	int	j;
	int	b;

	initialize_battlefield();
	diff = MEM_SIZE / vm->amount_players;
	i = -1;
	b = 0;
	while (++i < vm->amount_players)
	{
		j = -1;
		while (++j < PLAYER(i).code_size)
		{
			g_battlefield[b].code = PLAYER(i).code[j];
			if (i == 0)
				g_battlefield[b].color = 'r';
			else if (i == 1)
				g_battlefield[b].color = 'y';
			else if (i == 2)
				g_battlefield[b].color = 'g';
			else if (i == 3)
				g_battlefield[b].color = 'b';
			b++;
		}
		while ((b < diff && i == 0) || (b < MIN(diff * 2, MEM_SIZE) && i == 1) || (b < MIN(diff * 3, MEM_SIZE) && i == 2) || (b < MEM_SIZE && i == 3))
		{
			g_battlefield[b].code = 0x0;
			g_battlefield[b].color = '\0';
			b++;
		}
	}
	int	temp = 0;
	for (int c = 0; c < MEM_SIZE; c++)
	{
		if (temp == 64)
		{
			ft_printf("\n");
			temp = 0;
		}
		if (g_battlefield[c].color == 'r')
		{
			print_zero(RED, g_battlefield[c].code);
			ft_printf("%{red}hhx ", g_battlefield[c].code);
		}
		else if (g_battlefield[c].color == 'y')
		{
			print_zero(YELLOW, g_battlefield[c].code);
			ft_printf("%{yellow}hhx ", g_battlefield[c].code);
		}
		else if (g_battlefield[c].color == 'g')
		{
			print_zero(GREEN, g_battlefield[c].code);
			ft_printf("%{green}hhx ", g_battlefield[c].code);
		}
		else if (g_battlefield[c].color == 'b')
		{
			print_zero(BLUE, g_battlefield[c].code);
			ft_printf("%{blue}hhx ", g_battlefield[c].code);
		}
		else
		{
			print_zero(NORMAL, g_battlefield[c].code);
			ft_printf("%hhx ", g_battlefield[c].code);
		}
		temp++;
	}
	ft_printf("\n");
}
