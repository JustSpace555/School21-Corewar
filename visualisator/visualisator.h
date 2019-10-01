#ifndef VISUALISATOR_H
# define VISUALISATOR_H

#include "SDL2.framework/Headers/SDL.h"
#include "SDL2_ttf.framework/Headers/SDL_ttf.h"
#include "../VM/Headers/virtual_header.h"

#define			SCREEN_WIDTH 1920
#define			SCREEN_HEIGHT 1080
#define			SCREEN_FPS 244
#define			SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS
#define			INFORMATION_SIZE 350

SDL_Window		*g_main_window;
SDL_Renderer	*g_main_render;
SDL_Texture		**g_textures_array;

void			push_to_render_battlefield(SDL_FRect cell);
void			push_info(int current_cycle, int cycle_to_die, TTF_Font *font, int amount_players, int amount_checks, char *status);
void			push_int_text(int data, char *info_text, float y, TTF_Font *font, SDL_Color color);
void			push_int_slash_data(float y, TTF_Font *font, int data_1, int data_2, char *text, SDL_Color color);
void			push_char_text(char *text, float y, TTF_Font *font, SDL_Color color);
void			push_live_breakdown(int y, int amount_players);
void			push_pause(TTF_Font *font);
void			push_distribution(float y);
void			push_players(int start_y, int amount_players, TTF_Font *font);
void			set_render_draw_color(char color);
void			set_sdl_color(SDL_Color *color, int i);
int				init(void);
SDL_Texture		**make_code_text_array(TTF_Font *font);

#endif
