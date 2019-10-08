#include "../Headers/virtual_header.h"

int		ft_is_strdigit(char *str)
{
	if (!str || *str == '\0')
		return (-1);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}
