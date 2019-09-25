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
	push_char_text("Live breakdown for now:", SCREEN_HEIGHT - 80, font, White);
	push_live_breakdown(SCREEN_HEIGHT - 60, amount_players);
	push_char_text("Arena distribution: ", SCREEN_HEIGHT - 40, font, White);
	push_distribution(SCREEN_HEIGHT - 20);
	push_players(200, amount_players, font);
}

void	push_to_render_battlefield(SDL_FRect cell, SDL_Texture **array, TTF_Font *code_font)
{
	int			i;
	int			j;
	int			lines_count;
	SDL_Rect	code_cell;

	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderClear(g_main_render);
	i = -1;
	lines_count = 0;
	array = NULL;
	while (++i < (float)MEM_SIZE / 64)
	{
		j = -1;
		while (++j < (float)MEM_SIZE / 64)
		{
			cell.x = cell.w * j;
			cell.y = cell.h * i;
			SDL_SetRenderDrawColor(g_main_render,
				MIN(BATTLEFIELD_CELL(i, j, lines_count).color_r + BATTLEFIELD_CELL(i, j, lines_count).write_cycles, 255),
				MIN(BATTLEFIELD_CELL(i, j, lines_count).color_g + BATTLEFIELD_CELL(i, j, lines_count).write_cycles, 255),
				MIN(BATTLEFIELD_CELL(i, j, lines_count).color_b + BATTLEFIELD_CELL(i, j, lines_count).write_cycles, 255), 255);
			if (BATTLEFIELD_CELL(i, j, lines_count).write_cycles > 0)
				BATTLEFIELD_CELL(i, j, lines_count).write_cycles--;
			code_cell.x = (int)cell.x + 6;
			code_cell.y = (int)cell.y + 3;
			TTF_SizeText(code_font, (char *)&BATTLEFIELD_CELL(i, j, lines_count).code, &code_cell.w, &code_cell.h);
			if (BATTLEFIELD_CELL(i, j, lines_count).code == 0)
			{
				code_cell.w = 16;
				code_cell.h = 15;
			}
			SDL_RenderFillRectF(g_main_render, &cell);
			// if (BATTLEFIELD_CELL(i, j, lines_count).color != 'n')
				// SDL_RenderCopy(g_main_render, array[BATTLEFIELD_CELL(i, j, lines_count).code], NULL, &code_cell);
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
