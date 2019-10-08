#include "../Headers/virtual_header.h"

void	print_battlefield(void)
{
	int	print_bytes;
	int	c;

	print_bytes = 0;
	c = -1;
	ft_printf("0x%04x : ", print_bytes);
	while (++c < MEM_SIZE)
	{
		if (print_bytes % CODE_PER_LINE == 0 && print_bytes != 0)
			ft_printf("\n0x%04x : ", print_bytes);
		print_battlefield_help(c);
		print_bytes++;
	}
	ft_printf("\n");
}

void	print_sti(t_cursor *cursor, int reg, int sec_arg, int third_arg)
{
	ft_printf("P %4d | sti r%d %d %d\n", cursor->cursror_id,
									reg, sec_arg, third_arg);
	ft_printf("      | -> store to %d + %d = %d (with pc and mod %d)\n",
								sec_arg, third_arg, sec_arg + third_arg,
					cursor->cur_pos + ((sec_arg + third_arg) % IDX_MOD));
}

void	introduce(void)
{
	int	i;

	i = -1;
	ft_printf("Introducing contestants...\n");
	while (++i < g_vm->amount_players)
		ft_printf("* Player %d, weighting %d bytes, \"%s\" (\"%s\") !\n",
			PLAYER(i).identifier, PLAYER(i).code_size,
			PLAYER(i).name, PLAYER(i).comment);
}

void	push_vis(t_cycles_to_die repeate, char *status)
{
	push_to_render_battlefield();
	push_info(repeate.amount_of_repeate, status);
	SDL_RenderPresent(g_main_render);
}

void	push_winner_terminal(void)
{
	int	i;
	int	id;
	int	max;

	i = -1;
	max = 0;
	while (++i < g_vm->amount_players)
		if (PLAYER(i).last_alive > max)
		{
			max = PLAYER(i).last_alive;
			id = i;
		}
	ft_printf("Contestant %d, \"%s\", has won !\n", id + 1, PLAYER(id).name);
}
