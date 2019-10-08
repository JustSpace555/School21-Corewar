#include "../Headers/virtual_header.h"

int		check_file(char *argument)
{
	int		i;
	int		flag_dot;
	char	*extansion;

	extansion = "cor";
	flag_dot = 0;
	i = -1;
	while (argument[++i])
	{
		if (argument[i] == '.')
			flag_dot = 1;
		else if (flag_dot == 1)
		{
			if (argument[i] == *extansion)
			{
				extansion++;
				if (!(*extansion))
					flag_dot = 2;
			}
			else
				return (-1);
		}
		else if (flag_dot == 2)
			return (-1);
	}
	if (flag_dot == 2)
		return (1);
	return (flag_dot == 1) ? -1 : 0;
}

int		handler_n(int nbr, t_vm *flags, int index)
{
	if (nbr < 1 || nbr > MAX_PLAYERS)
		return (-1);
	if (flags->order_idtfrs[nbr - 1] == 0)
	{
		flags->plr_nbr[nbr - 1].identifier = nbr;
		flags->plr_nbr[nbr - 1].index_file = index;
		flags->order_idtfrs[nbr - 1] = 1;
	}
	else
		return (-1);
	return (1);
}

int		check_flags(int argc, char **argv, int *i, t_vm *vm)
{
	int rtn;

	rtn = -1;
	if (ft_strcmp("-dump", argv[*i]) == 0)
	{
		if (*i + 1 != argc)
			if (ft_is_strdigit(argv[*i + 1]) == 1)
			{
				vm->dump = ft_atoi(argv[*i + 1]);
				rtn = 1;
				*i += 1;
			}
	}
	else if (ft_strcmp("-n", argv[*i]) == 0)
	{
		if (*i + 2 != argc)
			if (ft_is_strdigit(argv[*i + 1]) == 1
				&& check_file(argv[*i + 2]) == 1)
			{
				rtn = handler_n(ft_atoi(argv[*i + 1]), vm, *i + 2);
				vm->amount_players++;
				*i += 2;
			}
	}
	else if (ft_strcmp("-v", argv[*i]) == 0)
	{
		if (*i + 1 != argc)
			if (ft_is_strdigit(argv[*i + 1]) == 1)
			{
				vm->ver = ft_atoi(argv[*i + 1]);
				rtn = 1;
				*i += 1;
			}
	}
	else if (ft_strcmp("-vi", argv[*i]) == 0)
	{
		vm->vis = 1;
		rtn = 1;
	}
	return (rtn);
}

int		parsing_arguments(int argc, char **argv, t_vm *vm)
{
	int	i;
	int res;

	i = 0;
	res = -1;
	while (++i < argc)
	{
		res = check_file(argv[i]);
		if (res == -1)
		{
			ft_printf("%s - invalid file name\n", argv[i]);
			return (-1);
		}
		else if (res == 1)
		{
			vm->amount_players++;
			continue;
		}
		else
			res = check_flags(argc, argv, &i, vm);
	}
	return (res);
}
