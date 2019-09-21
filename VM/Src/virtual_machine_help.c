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

int		choose_reverse_color(char color)
{
	if (color == 'r')
		return(0);
	else if (color == 'y')
		return(1);
	else if (color == 'g')
		return(2);
	else if (color == 'b')
		return(3);
	else if (color == 'p')
		return(4);
	else if (color == 'c')
		return(5);
	else if (color == 'e')
		return(6);
	else if (color == 'l')
		return (7);
	return (8);
}
