#include "../Headers/virtual_header.h"

void	choose_color_pt3(t_battlefield *cell, int i)
{
	if (i == 7)
	{
		cell->color = 'l';
		cell->color_r = 50;
		cell->color_g = 50;
		cell->color_b = 50;
	}
}

void	choose_color_pt2(t_battlefield *cell, int i)
{
	if (i == 4)
	{
		cell->color = 'p';
		cell->color_r = 128;
		cell->color_b = 128;
	}
	else if (i == 5)
	{
		cell->color = 'c';
		cell->color_g = 155;
		cell->color_b = 155;
	}
	else if (i == 6)
	{
		cell->color = 'e';
		cell->color_r = 169;
		cell->color_g = 169;
		cell->color_b = 169;
	}
	else
		choose_color_pt3(cell, i);
}

void	choose_color(t_battlefield *cell, int i)
{
	if (i == 0)
	{
		cell->color = 'r';
		cell->color_r = 155;
	}
	else if (i == 1)
	{
		cell->color = 'y';
		cell->color_r = 155;
		cell->color_g = 155;
	}
	else if (i == 2)
	{
		cell->color = 'g';
		cell->color_g = 128;
	}
	else if (i == 3)
	{
		cell->color = 'b';
		cell->color_b = 155;
	}
	else
		choose_color_pt2(cell, i);
}

char	choose_color_char(int i)
{
	if (i == 0)
		return ('r');
	else if (i == 1)
		return ('y');
	else if (i == 2)
		return ('g');
	else if (i == 3)
		return ('b');
	else if (i == 4)
		return ('p');
	else if (i == 5)
		return ('c');
	else if (i == 6)
		return ('e');
	else if (i == 7)
		return ('b');
	return ('n');
}
