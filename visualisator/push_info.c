#include "visualisator.h"

void	push_distribution(float y)
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
	coor.y = y;
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

void	push_live_breakdown(int y, int amount_players)
{
	int			i;
	float		k;
	SDL_FRect	coor;

	coor.y = y;
	coor.x = SCREEN_WIDTH - INFORMATION_SIZE + 25;
	coor.h = 15;
	if (g_amount_live_operations > 0)
	{
		k = 300 / (float)g_amount_live_operations;
		i = -1;
		while (++i < amount_players)
		{
			coor.w = PLAYER(i).nbr_live * k;
			set_render_draw_color(choose_color_char(i));
			SDL_RenderFillRectF(g_main_render, &coor);
			coor.x += coor.w;
		}
	}
	else
	{
		SDL_SetRenderDrawColor(g_main_render, 255, 255, 255, 255);
		coor.w = INFORMATION_SIZE - 50;
		SDL_RenderDrawRectF(g_main_render, &coor);
	}
}

void	push_int_text(int data, char *info_text, float y, TTF_Font *font, SDL_Color color)
{
	char		*temp_1;
	char		*temp_2;
	SDL_Surface	*text_surface = NULL;
	SDL_Texture	*text_texture = NULL;
	SDL_Rect	coor;

	temp_1 = ft_itoa(data);
	temp_2 = ft_strjoin(info_text, temp_1);
	ft_strdel(&temp_1);
	text_surface = TTF_RenderText_Solid(font, temp_2, color);
	if (text_surface)
	{
		text_texture = SDL_CreateTextureFromSurface(g_main_render, text_surface);
		SDL_FreeSurface(text_surface);
		TTF_SizeText(font, temp_2, &coor.w, &coor.h);
		ft_strdel(&temp_2);
		coor.x = SCREEN_WIDTH - INFORMATION_SIZE + 50;
		coor.y = y;
		SDL_RenderCopy(g_main_render, text_texture, NULL, &coor);
		SDL_DestroyTexture(text_texture);
	}
}

void	push_int_slash_data(float y, TTF_Font *font, int data_1, int data_2, char *text, SDL_Color color)
{
	char		*temp_1;
	char		*temp_2;
	char		*temp_3;
	SDL_Surface	*text_surface = NULL;
	SDL_Texture	*text_texture = NULL;
	SDL_Rect	coor;

	temp_1 = ft_itoa(data_1);
	temp_2 = ft_itoa(data_2);
	temp_3 = ft_strjoin_n(4, text, temp_1, "/", temp_2);
	ft_strdel(&temp_1);
	ft_strdel(&temp_2);
	text_surface = TTF_RenderText_Solid(font, temp_3, color);
	if (text_surface)
	{
		text_texture = SDL_CreateTextureFromSurface(g_main_render, text_surface);
		SDL_FreeSurface(text_surface);
		TTF_SizeText(font, temp_3, &coor.w, &coor.h);
		ft_strdel(&temp_3);
		coor.x = SCREEN_WIDTH - INFORMATION_SIZE + 50;
		coor.y = y;
		SDL_RenderCopy(g_main_render, text_texture, NULL, &coor);
		SDL_DestroyTexture(text_texture);
	}
}

void	push_char_text(char *text, float y, TTF_Font *font, SDL_Color color)
{
	SDL_Surface	*text_surface;
	SDL_Texture	*text_texture;
	SDL_Rect	coor;

	TTF_SizeText(font, text, &coor.w, &coor.h);
	coor.x = SCREEN_WIDTH - INFORMATION_SIZE + 50;
	coor.y = y;
	text_surface = TTF_RenderText_Solid(font, text, color);
	text_texture = SDL_CreateTextureFromSurface(g_main_render, text_surface);
	SDL_FreeSurface(text_surface);
	SDL_RenderCopy(g_main_render, text_texture, NULL, &coor);
	SDL_DestroyTexture(text_texture);
}

void	push_players(int start_y, int amount_players, TTF_Font *font)
{
	int	i;
	int	pos;
	SDL_Color	White = {255, 255, 255, 255};
	SDL_Color	color;

	i = -1;
	pos = start_y;
	while (++i < amount_players)
	{
		push_int_text(i + 1, "Player # ", pos, font, White);
		set_sdl_color(&color, i);
		push_char_text(PLAYER(i).name, pos + 20, font, color);
		push_int_text(PLAYER(i).identifier, "ID: ", pos + 40, font, White);
		push_int_text(PLAYER(i).last_alive, "Last alive: ", pos + 60, font, White);
		push_int_text(PLAYER(i).nbr_live, "Lives in current period : ", pos + 80, font, White);
		pos += 120;
	}
}
