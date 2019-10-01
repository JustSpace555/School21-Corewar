#include "visualisator.h"

void	push_info(int current_cycle, int cycle_to_die, TTF_Font *font, int amount_players, int amount_checks, char *status)
{
	SDL_Color	White = {255, 255, 255, 255};

	push_char_text(status, 20, font, White);
	push_int_text(g_cursors_amount, "Total processes: ", 40, font, White);
	push_int_text(current_cycle, "Current cycle: ", 60, font, White);
	push_int_text(cycle_to_die, "Cycle to die: ", 100, font, White);
	push_int_text(CYCLE_DELTA, "Cycle delta: ", 120, font, White);
	push_int_slash_data(160, font, g_amount_live_operations, NBR_LIVE, "NBR_live: ", White);
	push_int_slash_data(180, font, amount_checks, MAX_CHECKS, "MAX_checks: ", White);
	push_char_text("Live breakdown for now:", SCREEN_HEIGHT - 80, font, White);
	push_live_breakdown(SCREEN_HEIGHT - 60, amount_players);
	push_char_text("Arena distribution: ", SCREEN_HEIGHT - 40, font, White);
	push_distribution(SCREEN_HEIGHT - 20);
	push_players(220, amount_players, font);
}

void	push_to_render_battlefield(SDL_FRect cell)
{
	int			i;
	int			j;
	int			lines_count;

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

void	push_pause(TTF_Font *font)
{
	SDL_Rect	pause;
	SDL_Color	White = {255, 255, 255, 255};

	pause.h = 20;
	pause.w = 300;
	pause.y = 20;
	pause.x = SCREEN_WIDTH - INFORMATION_SIZE + 50;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderFillRect(g_main_render, &pause);
	push_char_text("**Pause**", 20, font, White);
	SDL_RenderPresent(g_main_render);
}
