#include "visualisator.h"

int		init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize. SDL error: %s\n", SDL_GetError());
		return (0);
	}
	g_main_window = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_main_window == NULL)
	{
		printf("SDL could not create window. SDL error: %s\n", SDL_GetError());
		return (0);
	}
	g_main_render = SDL_CreateRenderer(g_main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(g_main_render == NULL )
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return (0);
	}
	if (TTF_Init() < 0)
	{
		printf("SDL_ttf couldn't initialize. SDL error: %s\n", TTF_GetError());
		return (0);
	}
	return (1);
}

char	result(int num)
{
	if (num < 10)
		return (num + '0');
	if (num == 10)
		return ('a');
	else if (num == 11)
		return ('b');
	else if (num == 12)
		return ('c');
	else if (num == 13)
		return ('d');
	else if (num == 14)
		return ('e');
	return('f');
}

char	*get_text_from_cell(unsigned char code)
{
	char	*text;

	text = (char *)malloc(sizeof(char) * 2);
	text[0] = result(code / 16);
	text[1] = result(code % 16);
	return (text);
}

void	push_to_render(void)
{
	SDL_FRect	cell;
	float		i;
	float		j;
	int			lines_count;

	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderClear(g_main_render);
	i = -1;
	lines_count = 0;
	cell.w = (float)(SCREEN_WIDTH - 350) / 64;
	cell.h = (float)SCREEN_HEIGHT / 64;
	while (++i < (float)MEM_SIZE / 64 - 1)
	{
		j = -1;
		while (++j < (float)MEM_SIZE / 64 - 1)
		{
			cell.x = cell.w * j;
			cell.y = cell.h * i;
			if (g_battlefield[(int)(i + j + lines_count)].cursor)
			{
				if (g_battlefield[(int)(i + j + lines_count)].cursor_color == 'r')
					SDL_SetRenderDrawColor(g_main_render, 255, 0, 0, 255);
				else if (g_battlefield[(int)(i + j + lines_count)].cursor_color == 'y')
					SDL_SetRenderDrawColor(g_main_render, 255, 255, 0, 255);
				else if (g_battlefield[(int)(i + j + lines_count)].cursor_color == 'g')
					SDL_SetRenderDrawColor(g_main_render, 0, 128, 0, 255);
				else if (g_battlefield[(int)(i + j + lines_count)].cursor_color == 'b')
					SDL_SetRenderDrawColor(g_main_render, 0, 0, 255, 255);
				else if (g_battlefield[(int)(i + j + lines_count)].cursor_color == 'p')
					SDL_SetRenderDrawColor(g_main_render, 128, 0, 128, 255);
				else if (g_battlefield[(int)(i + j + lines_count)].cursor_color == 'c')
					SDL_SetRenderDrawColor(g_main_render, 0, 255, 255, 255);
				else if (g_battlefield[(int)(i + j + lines_count)].cursor_color == 'e')
					SDL_SetRenderDrawColor(g_main_render, 0, 255, 255, 255);
				else if (g_battlefield[(int)(i + j + lines_count)].cursor_color == 'l')
					SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
				SDL_RenderFillRectF(g_main_render, &cell);
			}
			else
			{
				if (g_battlefield[(int)(i + j + lines_count)].color == 'r')
					SDL_SetRenderDrawColor(g_main_render, 255, 0, 0, 100);
				else if (g_battlefield[(int)(i + j + lines_count)].color == 'y')
					SDL_SetRenderDrawColor(g_main_render, 255, 255, 0, 100);
				else if (g_battlefield[(int)(i + j + lines_count)].color == 'g')
					SDL_SetRenderDrawColor(g_main_render, 0, 128, 0, 100);
				else if (g_battlefield[(int)(i + j + lines_count)].color == 'b')
					SDL_SetRenderDrawColor(g_main_render, 0, 0, 255, 100);
				else if (g_battlefield[(int)(i + j + lines_count)].color == 'p')
					SDL_SetRenderDrawColor(g_main_render, 128, 0, 128, 100);
				else if (g_battlefield[(int)(i + j + lines_count)].color == 'c')
					SDL_SetRenderDrawColor(g_main_render, 0, 255, 255, 100);
				else if (g_battlefield[(int)(i + j + lines_count)].color == 'e')
					SDL_SetRenderDrawColor(g_main_render, 0, 255, 255, 100);
				else if (g_battlefield[(int)(i + j + lines_count)].color == 'l')
					SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 100);
				else
					SDL_SetRenderDrawColor(g_main_render, 47, 79, 79, 100);
				SDL_RenderDrawRectF(g_main_render, &cell);
			}
			SDL_RenderCopyF(g_main_render, g_textures_array[g_battlefield[(int)(i + j + lines_count)].code], NULL, &cell);
		}
		lines_count += j;
	}
}

void	initialize_textures(TTF_Font *font)
{
	int			i;
	SDL_Surface	*text_surface;
	SDL_Color	White = {255, 255, 255, 255};

	g_textures_array = (SDL_Texture **)(malloc(sizeof(SDL_Texture *) * 256));
	i = -1;
	while (++i < 256)
	{
		text_surface = TTF_RenderText_Solid(font, get_text_from_cell((unsigned char)i), White);
		g_textures_array[i] = SDL_CreateTextureFromSurface(g_main_render, text_surface);
		free(text_surface);
	}
}
