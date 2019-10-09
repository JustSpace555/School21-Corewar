#include "../Headers/virtual_header.h"

void	fill_free_space_battlefield(int *byte, int diff)
{
	while ((float)*byte < diff && *byte < MEM_SIZE)
	{
		g_battlefield[*byte].color_b = 111;
		g_battlefield[*byte].color_g = 111;
		g_battlefield[*byte].color_r = 111;
		g_battlefield[*byte].code = 0x0;
		g_battlefield[*byte].color = 'n';
		(*byte)++;
	}
}
