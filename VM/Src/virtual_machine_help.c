#include "../Headers/virtual_header.h"

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
	else if (i == 4)
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
	else if (i == 7)
	{
		cell->color = 'l';
		cell->color_r = 50;
		cell->color_g = 50;
		cell->color_b = 50;
	}
}

char	choose_color_char(int i)
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
		return ('b');
	return ('n');
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
	else if (cell->color == 'b')
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
	else if (cell->color == 'e')
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

void	free_all(TTF_Font *font, t_vm *vm)
{
	int	i;

	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(g_main_render);
	SDL_DestroyWindow(g_main_window);
	SDL_Quit();
	i = -1;
	while (++i < vm->amount_players)
	{
		free(PLAYER(i).code);
		free(PLAYER(i).comment);
		free(PLAYER(i).name);
	}
	free(g_battlefield);
	free(g_cursors);
}
