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
		if (g_vm->color_print)
			print_battlefield_help(c);
		else
			ft_printf("%02hhx ", g_battlefield[c].code);
		print_bytes++;
	}
	ft_printf("\n");
}

void	introduce(void)
{
	int	i;

	i = -1;
	ft_printf("Introducing contestants...\n");
	while (++i < g_vm->amount_players)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			PLAYER(i).identifier, PLAYER(i).code_size,
			PLAYER(i).name, PLAYER(i).comment);
}

void	push_vis(t_cycles_to_die repeate, char *status)
{
	push_to_render_battlefield();
	push_info(repeate.amount_of_repeate, status);
	SDL_RenderPresent(g_main_render);
}

void	print_pc_movement(t_cursor *cursor, int skip)
{
	int	i;

	if (g_vm->ver == 5 || g_vm->ver == 30)
	{
		i = -1;
		ft_printf("ADV %d (0x%04x -> 0x%04x) ", skip, cursor->cur_pos, cursor->cur_pos + skip);
		while (++i < skip)
			ft_printf("%02hhx ", g_battlefield[(cursor->cur_pos + i)].code);
		ft_printf("\n");
	}
}
