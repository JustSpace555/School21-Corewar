#include "vizualizator.h"

void	push_info(int amount_checks, char *status)
{
	SDL_Color	White = {255, 255, 255, 255};

	push_char_text(status, 20, White);
	push_int_text(g_cursors_amount, "Total processes: ", 40, White);
	push_int_text(CURRENT_CYCLE, "Current cycle: ", 60, White);
	push_int_text(CTD, "Cycle to die: ", 100, White);
	push_int_text(CYCLE_DELTA, "Cycle delta: ", 120, White);
	push_int_slash_data(160, g_amount_live_operations, NBR_LIVE, "NBR_live: ", White);
	push_int_slash_data(180, amount_checks, MAX_CHECKS, "MAX_checks: ", White);
	push_char_text("Live breakdown for now:", SCREEN_HEIGHT - 80, White);
	push_live_breakdown(SCREEN_HEIGHT - 60);
	push_char_text("Arena distribution: ", SCREEN_HEIGHT - 40, White);
	push_distribution(SCREEN_HEIGHT - 20);
	push_players(220);
}

void	push_to_render_battlefield(void)
{
	int			i;
	int			j;
	int			lines_count;
	SDL_FRect	cell;

	cell.w = (float)(SCREEN_WIDTH - INFORMATION_SIZE) / 64;
	cell.h = (float)SCREEN_HEIGHT / 64;
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
			SDL_SetRenderDrawColor(g_main_render,
				g_battlefield[i + j + lines_count].color_r + g_battlefield[i + j + lines_count].write_cycles,
				g_battlefield[i + j + lines_count].color_g + g_battlefield[i + j + lines_count].write_cycles,
				g_battlefield[i + j + lines_count].color_b + g_battlefield[i + j + lines_count].write_cycles, 255);
			if (!VIS_PAUSE && g_battlefield[i + j + lines_count].write_cycles > 0)
				g_battlefield[i + j + lines_count].write_cycles--;
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

void	push_pause(void)
{
	SDL_Rect	pause;
	SDL_Color	White = {255, 255, 255, 255};

	pause.h = 20;
	pause.w = 300;
	pause.y = 20;
	pause.x = SCREEN_WIDTH - INFORMATION_SIZE + 50;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderFillRect(g_main_render, &pause);
	push_char_text("**Pause**", 20, White);
	SDL_RenderPresent(g_main_render);
}
