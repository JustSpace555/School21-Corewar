#include "../Headers/virtual_header.h"

int		check_for_cycle_exec(t_cursor *cursor)
{
	if (cursor->cycle_exec > 0)
	{
		cursor->cycle_exec--;
		if (cursor->cycle_exec > 0)
			return (-1);
	}
	cursor->cycle_exec = -1;
	return (1);
}

int		get_var_byte(unsigned char code, int offset, int label_size)
{
	code <<= offset;
	if ((code & 0xC0) == 192)
		return (2);
	else if ((code & 0x80) == 128)
		return (label_size);
	else if ((code & 0x40) == 64)
		return (1);
	return (0);
}

int		get_amount_bytes_to_skip(unsigned char code,
				int label_size, int amount_arguments)
{
	int	skip;
	int	i;

	skip = 0;
	i = -1;
	while (++i < amount_arguments)
		skip += get_var_byte(code, i * 2, label_size);
	return (skip);
}

short	arena_truncation(short address)
{
	if (address > MEM_SIZE)
		address %= MEM_SIZE;
	if (address < 0)
		address = MEM_SIZE + address;
	return address;
}
void	write_amount_of_bytes_data(short addres, void *write,
								int size_of_write, char color)
{
	int				i;
	char			temp_1[2];
	char			temp_2[4];

	i = -1;

	addres = arena_truncation(addres);
	if (size_of_write == 2)
	{
		*(short *)temp_1 = *(short *)write;
		while (++i < 2)
		{
			g_battlefield[(addres + i) % MEM_SIZE].code = temp_1[1 - i];
			g_battlefield[(addres + i) % MEM_SIZE].color = color;
			choose_reverse_color(&g_battlefield[(addres + i) % MEM_SIZE]);
			g_battlefield[(addres + i) % MEM_SIZE].write_cycles = 100;
		}
	}
	else
	{
		*(unsigned int *)temp_2 = *(unsigned int *)write;
		while (++i < 4)
		{
			g_battlefield[(addres + i) % MEM_SIZE].code = temp_2[3 - i];
			g_battlefield[(addres + i) % MEM_SIZE].color = color;
			choose_reverse_color(&g_battlefield[(addres + i) % MEM_SIZE]);
			g_battlefield[(addres + i) % MEM_SIZE].write_cycles = 100;
		}
	}
}
