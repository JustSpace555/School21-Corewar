#include "vizualizator.h"

int			init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_printf("SDL could not initialize. SDL error: %s\n", SDL_GetError());
		return (0);
	}
	g_main_window = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_main_window == NULL)
	{
		ft_printf("SDL could not create window. SDL error: %s\n", SDL_GetError());
		return (0);
	}
	g_main_render = SDL_CreateRenderer(g_main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(g_main_render == NULL )
	{
		ft_printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return (0);
	}
	if (TTF_Init() < 0)
	{
		ft_printf("SDL_ttf couldn't initialize. SDL error: %s\n", TTF_GetError());
		return (0);
	}
	if (!(g_font = TTF_OpenFont("vizualizator/InputMono-Regular.ttf", 15)))
	{
		ft_printf("%s\n", TTF_GetError());
		return (0);
	}
	return (1);
}

void		set_render_draw_color(char color)
{
	if (color == 'r')
		SDL_SetRenderDrawColor(g_main_render, 155, 0, 0, 255);
	else if (color == 'y')
		SDL_SetRenderDrawColor(g_main_render, 155, 155, 0, 255);
	else if (color == 'g')
		SDL_SetRenderDrawColor(g_main_render, 0, 155, 0, 255);
	else if (color == 'b')
		SDL_SetRenderDrawColor(g_main_render, 0, 0, 155, 255);
	else if (color == 'p')
		SDL_SetRenderDrawColor(g_main_render, 155, 0, 155, 255);
	else if (color == 'c')
		SDL_SetRenderDrawColor(g_main_render, 0, 155, 155, 255);
	else if (color == 'e')
		SDL_SetRenderDrawColor(g_main_render, 155, 155, 155, 255);
	else if (color == 'l')
		SDL_SetRenderDrawColor(g_main_render, 50, 50, 50, 255);
	else
		SDL_SetRenderDrawColor(g_main_render, 111, 111, 111, 255);
}

void	set_sdl_color(SDL_Color *color, int i)
{
	if (i == 0 || i == 'r')
	{
		color->r = 155;
		color->g = 0;
		color->b = 0;
	}
	else if (i == 1 || i == 'y')
	{
		color->r = 155;
		color->g = 155;
		color->b = 0;
	}
	else if (i == 2 || i == 'g')
	{
		color->r = 0;
		color->g = 155;
		color->b = 0;
	}
	else if (i == 3 || i == 'b')
	{
		color->r = 0;
		color->g = 0;
		color->b = 155;
	}
	else if (i == 4 || i == 'p')
	{
		color->r = 155;
		color->g = 0;
		color->b = 155;
	}
	else if (i == 5 || i == 'c')
	{
		color->r = 0;
		color->g = 155;
		color->b = 155;
	}
	else if (i == 6 || i == 'e')
	{
		color->r = 155;
		color->g = 155;
		color->b = 155;
	}
	else if (i == 7 || i == 'l')
	{
		color->r = 50;
		color->g = 50;
		color->b = 50;
	}
	else if (i == 'n')
	{
		color->r = 111;
		color->g = 111;
		color->b = 111;
	}
}

void	visualisator_event(void)
{
	SDL_Event	event;

	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
			&& event.key.keysym.sym == SDLK_ESCAPE))
			VIS_QUIT = 1;
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		{
			if (VIS_PAUSE == 1)
				VIS_PAUSE = 0;
			else
				VIS_PAUSE = 1;
		}
	}
}
