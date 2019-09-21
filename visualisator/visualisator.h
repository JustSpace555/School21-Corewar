#ifndef VISUALISATOR_H
# define VISUALISATOR_H

#include "SDL2.framework/Headers/SDL.h"
#include "SDL2_ttf.framework/Headers/SDL_ttf.h"
#include "../VM/Headers/virtual_header.h"

#define			SCREEN_HEIGHT 1080
#define			SCREEN_WIDTH 1920
#define			SCREEN_FPS 244
#define			SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS
#define			INFORMATION_SIZE 350

SDL_Window		*g_main_window;
SDL_Renderer	*g_main_render;
SDL_Texture		**g_textures_array;

void			push_to_render_battlefield(SDL_FRect cell);
void			push_info(int current_cycle, int cycle_to_die, TTF_Font *font);
int				init(void);

#endif
