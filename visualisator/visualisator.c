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

void	set_render_draw_color(char color)
{
	if (color == 'r')
		SDL_SetRenderDrawColor(g_main_render, 155, 0, 0, 255);
	else if (color == 'y')
		SDL_SetRenderDrawColor(g_main_render, 155, 155, 0, 255);
	else if (color == 'g')
		SDL_SetRenderDrawColor(g_main_render, 0, 128, 0, 255);
	else if (color == 'b')
		SDL_SetRenderDrawColor(g_main_render, 0, 0, 155, 255);
	else if (color == 'p')
		SDL_SetRenderDrawColor(g_main_render, 128, 0, 128, 255);
	else if (color == 'c')
		SDL_SetRenderDrawColor(g_main_render, 0, 155, 155, 255);
	else if (color == 'e')
		SDL_SetRenderDrawColor(g_main_render, 169, 169, 169, 255);
	else if (color == 'l')
		SDL_SetRenderDrawColor(g_main_render, 50, 50, 50, 255);
	else
		SDL_SetRenderDrawColor(g_main_render, 111, 111, 111, 255);
}

SDL_Rect	set_rect(int x, int y, int h, int w)
{
	SDL_Rect	rect;

	rect.h = h;
	rect.w = w;
	rect.x = x;
	rect.y = y;
	return (rect);
}

void	set_info_text(void *data, int flag, TTF_Font *font, int indent_count, char *text)
{
	char		*temp_1;
	char		*temp_2;
	SDL_Surface	*text_surface;
	SDL_Texture	*text_texture;
	SDL_Color	White = {255, 255, 255, 255};
	SDL_Rect	coor;

	temp_1 = NULL;
	temp_2 = NULL;
	if (data)
	{
		if (flag)
		{
			printf("before = %d\n", *(int *)data);
			temp_1 = ft_itoa(*(int *)data);
			printf("after = %s\n", temp_1);
		}
		else
			temp_1 = (char *)data;
	}
	if (temp_1)
	{
		temp_2 = ft_strjoin(text, temp_1);
		text_surface = TTF_RenderText_Solid(font, temp_2, White);
		free(temp_1);
		free(temp_2);
	}
	else
		text_surface = TTF_RenderText_Solid(font, text, White);
	text_texture = SDL_CreateTextureFromSurface(g_main_render, text_surface);
	coor = set_rect(SCREEN_WIDTH - INFORMATION_SIZE + 50, 50 * indent_count, 17, 200);
	SDL_RenderCopy(g_main_render, text_texture, NULL, &coor);
}

void	push_distribution(int indent_count)
{
	int			colors[9];
	int			i;
	float		k;
	SDL_FRect	coor;

	k = 300 / (float)MEM_SIZE;
	i = -1;
	while (++i < 9)
		colors[i] = 0;
	i = -1;
	while (++i < MEM_SIZE)
		colors[choose_reverse_color(&g_battlefield[i])]++;
	i = -1;
	coor.y = 50 * indent_count;
	coor.x = SCREEN_WIDTH - INFORMATION_SIZE + 25;
	while (++i < 9)
	{
		coor.h = 15;
		coor.w = colors[i] * k;
		set_render_draw_color(choose_color_char(i));
		SDL_RenderFillRectF(g_main_render, &coor);
		coor.x += coor.w;
	}
}

void	push_info(int current_cycle, int cycle_to_die, TTF_Font *font)
{
	int	temp;

	temp = CYCLE_DELTA;
	set_info_text((void *)&g_cursors_amount, 1, font, 1, "Total processes: ");
	set_info_text((void *)&current_cycle, 1, font, 2, "Current cycle: ");
	set_info_text((void *)&cycle_to_die, 1, font, 3, "Cycle to die: ");
	set_info_text((void *)&temp, 1, font, 4, "Cycle delta: ");
	set_info_text(NULL, 0, font, 5, "Arena distribution: ");
	push_distribution(6);
}

void	push_to_render_battlefield(SDL_FRect cell)
{
	int	i;
	int	j;
	int	lines_count;

	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderClear(g_main_render);
	i = -1;
	lines_count = 0;
	while (++i < (float)MEM_SIZE / 64)
	{
		j = -1;
		while (++j < (float)MEM_SIZE / 64)
		{
			cell.x = cell.w * j;
			cell.y = cell.h * i;
			// set_render_draw_color(g_battlefield[i + j + lines_count].color);
			SDL_SetRenderDrawColor(g_main_render,
				BATTLEFIELD_CELL(i, j, lines_count).color_r + BATTLEFIELD_CELL(i, j, lines_count).write_cycles,
				BATTLEFIELD_CELL(i, j, lines_count).color_g + BATTLEFIELD_CELL(i, j, lines_count).write_cycles,
				BATTLEFIELD_CELL(i, j, lines_count).color_b + BATTLEFIELD_CELL(i, j, lines_count).write_cycles, 255);
			if (BATTLEFIELD_CELL(i, j, lines_count).write_cycles > 0)
				BATTLEFIELD_CELL(i, j, lines_count).write_cycles--;
			SDL_RenderFillRectF(g_main_render, &cell);
		}
		lines_count += j - 1;
	}
	i = -1;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	while (++i < (float)MEM_SIZE / 64)
	{
		SDL_RenderDrawLineF(g_main_render, cell.w * i, 0, cell.w * i, SCREEN_HEIGHT);
		SDL_RenderDrawLineF(g_main_render, 0, cell.h * i, SCREEN_WIDTH - INFORMATION_SIZE, cell.h * i);
	}
	i = -1;
	lines_count = 0;
	SDL_SetRenderDrawColor(g_main_render, 255, 255, 255, 255);
	while (++i < (float)MEM_SIZE / 64)
	{
		j = -1;
		while (++j < (float)MEM_SIZE / 64)
		{
			if (g_battlefield[i + j + lines_count].cursor)
			{
				cell.x = cell.w * j;
				cell.y = cell.h * i;
				SDL_RenderDrawRectF(g_main_render, &cell);
			}
		}
		lines_count += j - 1;
	}
}
