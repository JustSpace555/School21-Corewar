#include "../Headers/virtual_header.h"

char	choose_color(int i)
{
	if (i == 0)
		return('r');
	else if (i == 1)
		return('y');
	else if (i == 2)
		return('g');
	else if (i == 3)
		return('b');
	else if (i == 4)
		return('p');
	else if (i == 5)
		return('c');
	else if (i == 6)
		return('e');
	else if (i == 7)
		return ('l');
	return ('n');
}
