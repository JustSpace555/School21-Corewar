#ifndef VISUALISATOR_H
# define VISUALISATOR_H

#include "../VM/Headers/virtual_header.h"
#include "SDL2.framework/Headers/SDL.h"
#include "SDL2_ttf.framework/Headers/SDL_ttf.h"

#define			SCREEN_HEIGHT 1080
#define			SCREEN_WIDTH 1920
#define			SCREEN_FPS 120
#define			SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS

SDL_Window		*g_main_window;
SDL_Renderer	*g_main_render;

void			push_to_render(void);
t_bool			init(void);

#endif
