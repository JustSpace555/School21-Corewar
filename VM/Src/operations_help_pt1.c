#include "../Headers/virtual_header.h"

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
	return (address);
}

void	write_short_data(short addres, short write, char color)
{
	char	temp[2];
	int		i;

	i = -1;
	*(short *)temp = write;
	addres = arena_truncation(addres);
	while (++i < 2)
	{
		g_battlefield[(addres + i) % MEM_SIZE].code = temp[1 - i];
		g_battlefield[(addres + i) % MEM_SIZE].color = color;
		choose_reverse_color(&g_battlefield[(addres + i) % MEM_SIZE]);
		g_battlefield[(addres + i) % MEM_SIZE].write_cycles = 100;
	}
}

void	write_int_data(short addres, unsigned int write, char color)
{
	char	temp[4];
	int		i;

	i = -1;
	*(unsigned int *)temp = write;
	addres = arena_truncation(addres);
	while (++i < 4)
	{
		g_battlefield[(addres + i) % MEM_SIZE].code = temp[3 - i];
		g_battlefield[(addres + i) % MEM_SIZE].color = color;
		choose_reverse_color(&g_battlefield[(addres + i) % MEM_SIZE]);
		g_battlefield[(addres + i) % MEM_SIZE].write_cycles = 100;
	}
}
