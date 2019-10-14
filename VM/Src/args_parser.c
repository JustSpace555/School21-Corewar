/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:44:23 by cheller           #+#    #+#             */
/*   Updated: 2019/10/14 14:44:30 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

int		handler_dots(char *argument, int *flag_dot, char **extansion, int i)
{
	if (argument[i] == '.')
		*flag_dot += 1;
	else if (*flag_dot == 1)
	{
		if (argument[i] == **extansion)
		{
			(*extansion)++;
			if (!(**extansion))
				*flag_dot = 2;
		}
		else if (argument[i + 1] != 0)
			*flag_dot = 0;
		else
			return (-1);
	}
	else if (*flag_dot == 2 && argument[i] == '/')
		*flag_dot = 0;
	else if (*flag_dot >= 2)
		return (-1);
	return (1);
}

int		check_file(char *argument)
{
	int		i;
	int		flag_dot;
	char	*extansion;

	extansion = "cor";
	flag_dot = 0;
	i = -1;
	if (argument[0] == '-')
		return (0);
	while (argument[++i])
	{
		if (handler_dots(argument, &flag_dot, &extansion, i) == -1)
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

void	check_next_flags(int argc, char **argv, int *i, int *rtn)
{
	if (*rtn == 1)
		return ;
	if (ft_strcmp("-v", argv[*i]) == 0)
	{
		if (*i + 1 != argc)
			if (ft_is_strdigit(argv[*i + 1]) == 1)
			{
				g_vm->ver = ft_atoi(argv[*i + 1]);
				*rtn = 1;
				*i += 1;
			}
	}
	else if (ft_strcmp("-vi", argv[*i]) == 0)
	{
		g_vm->vis = 1;
		*rtn = 1;
	}
	else if (ft_strcmp("-a", argv[*i]) == 0)
	{
		g_vm->aff = 1;
		*rtn = 1;
	}
}

int		check_flags(int argc, char **ar, int *i)
{
	int rtn;

	rtn = -1;
	if (ft_strcmp("-dump", ar[*i]) == 0 || ft_strcmp("-dumpc", ar[*i]) == 0)
	{
		g_vm->color_print = (ft_strcmp("-dumpc", ar[*i]) == 0) ? 1 : 0;
		if (*i + 1 != argc)
			if (ft_is_strdigit(ar[*i + 1]) == 1)
			{
				g_vm->dump = ft_atoi(ar[*i + 1]);
				rtn = 1;
				*i += 1;
			}
	}
	else if (ft_strcmp("-n", ar[*i]) == 0)
		if (*i + 2 != argc)
			if (ft_is_strdigit(ar[*i + 1]) == 1 && check_file(ar[*i + 2]) == 1)
			{
				rtn = handler_n(ft_atoi(ar[*i + 1]), g_vm, *i + 2);
				g_vm->amount_players++;
				*i += 2;
			}
	check_next_flags(argc, ar, i, &rtn);
	return (rtn);
}
