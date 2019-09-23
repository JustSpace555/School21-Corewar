#include "visualisator.h"

void	push_info(int current_cycle, int cycle_to_die, TTF_Font *font, int amount_players, int amount_checks)
{
	SDL_Color	White = {255, 255, 255, 255};

	push_int_text(g_cursors_amount, "Total processes: ", 20, font, White);
	push_int_text(current_cycle, "Current cycle: ", 40, font, White);
	push_int_text(cycle_to_die, "Cycle to die: ", 80, font, White);
	push_int_text(CYCLE_DELTA, "Cycle delta: ", 100, font, White);
	push_int_slash_data(140, font, g_amount_live_operations, NBR_LIVE, "NBR_live: ", White);
	push_int_slash_data(160, font, amount_checks, MAX_CHECKS, "MAX_checks: ", White);
	push_players(200, amount_players, font);
	push_char_text("Arena distribution: ", SCREEN_HEIGHT - 40, font, White);
	push_distribution(SCREEN_HEIGHT - 20);
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
