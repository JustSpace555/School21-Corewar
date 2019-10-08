#include "../Headers/virtual_header.h"

void	print_hex_data_help(int count, uint8_t *buffer, int i)
{
	if (count < 4 || (count >= PROG_NAME_LENGTH + 12 && count <
			COMMENT_LENGTH + PROG_NAME_LENGTH + 12))
		ft_printf(RED"%02hhx "NORMAL, buffer[i]);
	else if (count >= 4 && count < PROG_NAME_LENGTH + 4)
		ft_printf(YELLOW"%02hhx "NORMAL, buffer[i]);
	else if ((count >= PROG_NAME_LENGTH + 4 && count <
				PROG_NAME_LENGTH + 8) || (count >= COMMENT_LENGTH
					+ 12 + PROG_NAME_LENGTH && count < COMMENT_LENGTH
						+ 16 + PROG_NAME_LENGTH))
		ft_printf(BLACK"%02hhx "NORMAL, buffer[i]);
	else if (count >= COMMENT_LENGTH + 16 + PROG_NAME_LENGTH
			|| (count >= PROG_NAME_LENGTH + 8 && count <
				PROG_NAME_LENGTH + 12))
		ft_printf(CYAN"%02hhx "NORMAL, buffer[i]);
}

void	print_battlefield_help(int c)
{
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
}
