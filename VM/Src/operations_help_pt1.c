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

int		get_amount_bytes_to_skip(unsigned char code, int label_size)
{
	int	skip;

	skip = get_var_byte(code, 0, label_size);
	skip += get_var_byte(code, 2, label_size);
	skip += get_var_byte(code, 4, label_size);
	skip += get_var_byte(code, 6, label_size);
	return (skip);
}

void	write_amount_of_bytes_data(short addres, void *write, int size_of_write, char color)
{
	int				i;
	char			temp_1[2];
	char			temp_2[4];

	i = -1;
	if (addres > MEM_SIZE)
		addres -= MEM_SIZE;
	if (size_of_write == 2)
	{
		*(short *)temp_1 = *(short *)write;
		while (++i < 2)
		{
			g_battlefield[addres + i].code = temp_1[1 - i];
			g_battlefield[addres + i].color = color;
			choose_reverse_color(&g_battlefield[addres + i]);
			g_battlefield[addres + i].write_cycles = 100;
		}
	}
	else
	{
		*(unsigned int *)temp_2 = *(unsigned int *)write;
		while (++i < 4)
		{
			g_battlefield[addres + i].code = temp_2[3 - i];
			g_battlefield[addres + i].color = color;
			choose_reverse_color(&g_battlefield[addres + i]);
			g_battlefield[addres + i].write_cycles = 100;
		}
	}
}
