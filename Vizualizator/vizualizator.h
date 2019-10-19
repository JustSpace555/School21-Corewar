#ifndef VIZUALIZATOR_H
# define VIZUALIZATOR_H

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
TTF_Font		*g_font;

void			push_to_render_battlefield(void);
void			push_info(int amount_checks, char *status);
void			push_int_text(int data, char *info_text, float y, SDL_Color color);
void			push_int_slash_data(float y, int data_1, int data_2, char *text, SDL_Color color);
void			push_char_text(char *text, float y, SDL_Color color);
void			push_live_breakdown(int y);
void			push_pause(void);
void			push_distribution(float y);
void			push_players(int start_y);
void			push_winner_vis(void);
void			set_render_draw_color(char color);
void			set_sdl_color(SDL_Color *color, int i);
int				init(void);
void			visualisator_event(void);

#endif
