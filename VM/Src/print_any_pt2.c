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
		if (g_battlefield[c].cursor)
			ft_printf(WHITE_BG"%{black}02hhx ", g_battlefield[c].code);
		else
		{
			if (g_battlefield[c].color == 'r')
				ft_printf("%{red}02hhx ", g_battlefield[c].code);
			else if (g_battlefield[c].color == 'y')
				ft_printf("%{yellow}02hhx ", g_battlefield[c].code);
			else if (g_battlefield[c].color == 'g')
				ft_printf("%{green}02hhx ", g_battlefield[c].code);
			else if (g_battlefield[c].color == 'b')
				ft_printf("%{blue}02hhx ", g_battlefield[c].code);
			else if (g_battlefield[c].color == 'p')
				ft_printf("%{purple}02hhx ", g_battlefield[c].code);
			else if (g_battlefield[c].color == 'c')
				ft_printf("%{cyan}02hhx ", g_battlefield[c].code);
			else if (g_battlefield[c].color == 'e')
				ft_printf("%{grey}02hhx ", g_battlefield[c].code);
			else if (g_battlefield[c].color == 'l')
				ft_printf("%{black}02hhx ", g_battlefield[c].code);
			else
				ft_printf("%02hhx ", g_battlefield[c].code);
		}
		print_bytes++;
	}
	ft_printf("\n");
}

void			print_sti(t_cursor *cursor, int reg, int sec_arg, int third_arg)
{
	ft_printf("P %4d | sti r%d %d %d\n", cursor->cursror_id, reg, sec_arg, third_arg);
	ft_printf("      | -> store to %d + %d = %d (with pc and mod %d)\n", sec_arg, third_arg, sec_arg + third_arg, cursor->cur_pos + ((sec_arg + third_arg) % IDX_MOD));
}
