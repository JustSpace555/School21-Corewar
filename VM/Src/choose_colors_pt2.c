#include "../Headers/virtual_header.h"

int		choose_reverse_color_pt3(t_battlefield *cell)
{
	if (cell->color == 'e')
	{
		cell->color_r = 169;
		cell->color_g = 169;
		cell->color_b = 169;
		return (6);
	}
	else if (cell->color == 'l')
	{
		cell->color_r = 50;
		cell->color_g = 50;
		cell->color_b = 50;
		return (7);
	}
	return (8);
}

int		choose_reverse_color_pt2(t_battlefield *cell)
{
	if (cell->color == 'b')
	{
		cell->color_r = 0;
		cell->color_g = 0;
		cell->color_b = 155;
		return (3);
	}
	else if (cell->color == 'p')
	{
		cell->color_r = 128;
		cell->color_g = 0;
		cell->color_b = 128;
		return (4);
	}
	else if (cell->color == 'c')
	{
		cell->color_r = 0;
		cell->color_g = 155;
		cell->color_b = 155;
		return (5);
	}
	return (choose_reverse_color_pt3(cell));
}

int		choose_reverse_color(t_battlefield *cell)
{
	if (cell->color == 'r')
	{
		cell->color_r = 155;
		cell->color_g = 0;
		cell->color_b = 0;
		return (0);
	}
	else if (cell->color == 'y')
	{
		cell->color_r = 155;
		cell->color_g = 155;
		cell->color_b = 0;
		return (1);
	}
	else if (cell->color == 'g')
	{
		cell->color_r = 0;
		cell->color_g = 128;
		cell->color_b = 0;
		return (2);
	}
	return (choose_reverse_color_pt2(cell));
}
