#include "visualisator.h"

t_bool	init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize. SDL error: %s\n", SDL_GetError());
		return (false);
	}
	g_main_window = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_main_window == NULL)
	{
		printf("SDL could not create window. SDL error: %s\n", SDL_GetError());
		return (false);
	}
	g_main_render = SDL_CreateRenderer(g_main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(g_main_render == NULL )
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return (false);
	}
	if (TTF_Init() < 0)
	{
		printf("SDL_ttf couldn't initialize. SDL error: %s\n", TTF_GetError());
		return (false);
	}
	return (true);
}

void	push_to_render(void)
{
	SDL_FRect	cell;
	int			i;
	int			j;
	int			lines_count;

	SDL_SetRenderDrawColor(g_main_render, 255, 255, 255, 255);
	SDL_RenderClear(g_main_render);
	i = -1;
	lines_count = 0;
	cell.w = (SCREEN_WIDTH - 350) / 64;
	cell.h = SCREEN_HEIGHT / 64;
	while (++i < MEM_SIZE / 64)
	{
		j = -1;
		while (++j < MEM_SIZE / 64)
		{
			cell.x = cell.w * j;
			cell.y = cell.h * i;
			// SDL_RenderDrawRectF(g_main_render, &cell);
			if (g_battlefield[i + j + lines_count].cursor)
			{
				if (g_battlefield[i + j + lines_count].cursor_color == 'r')
					SDL_SetRenderDrawColor(g_main_render, 255, 0, 0, 255);
				else if (g_battlefield[i + j + lines_count].cursor_color == 'y')
					SDL_SetRenderDrawColor(g_main_render, 255, 255, 0, 255);
				else if (g_battlefield[i + j + lines_count].cursor_color == 'g')
					SDL_SetRenderDrawColor(g_main_render, 0, 128, 0, 255);
				else if (g_battlefield[i + j + lines_count].cursor_color == 'b')
					SDL_SetRenderDrawColor(g_main_render, 0, 0, 255, 255);
				else if (g_battlefield[i + j + lines_count].cursor_color == 'p')
					SDL_SetRenderDrawColor(g_main_render, 128, 0, 128, 255);
				else if (g_battlefield[i + j + lines_count].cursor_color == 'c')
					SDL_SetRenderDrawColor(g_main_render, 0, 255, 255, 255);
				else if (g_battlefield[i + j + lines_count].cursor_color == 'e')
					SDL_SetRenderDrawColor(g_main_render, 0, 255, 255, 255);
				else if (g_battlefield[i + j + lines_count].cursor_color == 'l')
					SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
				else
					SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
			}
			else
			{
				if (g_battlefield[i + j + lines_count].color == 'r')
					SDL_SetRenderDrawColor(g_main_render, 255, 0, 0, 100);
				else if (g_battlefield[i + j + lines_count].color == 'y')
					SDL_SetRenderDrawColor(g_main_render, 255, 255, 0, 100);
				else if (g_battlefield[i + j + lines_count].color == 'g')
					SDL_SetRenderDrawColor(g_main_render, 0, 128, 0, 100);
				else if (g_battlefield[i + j + lines_count].color == 'b')
					SDL_SetRenderDrawColor(g_main_render, 0, 0, 255, 100);
				else if (g_battlefield[i + j + lines_count].color == 'p')
					SDL_SetRenderDrawColor(g_main_render, 128, 0, 128, 100);
				else if (g_battlefield[i + j + lines_count].color == 'c')
					SDL_SetRenderDrawColor(g_main_render, 0, 255, 255, 100);
				else if (g_battlefield[i + j + lines_count].color == 'e')
					SDL_SetRenderDrawColor(g_main_render, 0, 255, 255, 100);
				else if (g_battlefield[i + j + lines_count].color == 'l')
					SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 100);
				else
					SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 10);
			}
			SDL_RenderFillRectF(g_main_render, &cell);
			lines_count += j;
		}
	}
}

// void	visualisator(t_vm *vm)
// {

// }
