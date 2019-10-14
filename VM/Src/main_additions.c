/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_additions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:16 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 13:54:45 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

int		check_unattached_index(int index, t_plr_nbr *plr_nbr)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (plr_nbr[i].index_file == index)
			return (0);
	}
	return (1);
}

int		find_unattached_file(t_vm *vm, char **argv, int argc)
{
	static int i;

	i = 0;
	while (++i < argc)
	{
		if (ft_strstr(argv[i], ".cor") &&
				check_unattached_index(i, vm->plr_nbr))
			return (i);
	}
	return (0);
}

void	set_identifiers(t_vm *vm, int argc, char **argv)
{
	int i;

	i = -1;
	while (++i < vm->amount_players)
	{
		if (vm->order_idtfrs[i] == 0)
		{
			vm->plr_nbr[i].index_file = find_unattached_file(vm, argv, argc);
			vm->plr_nbr[i].identifier = i + 1;
		}
	}
}

int		parsing(int argc, char **argv)
{
	int		i;
	char	**player_files;

	if (parsing_arguments(argc, argv, g_vm) == -1)
		return (-1);
	if (g_vm->amount_players > MAX_PLAYERS)
	{
		write(2, "Too many champions\n", 19);
		return (-1);
	}
	set_identifiers(g_vm, argc, argv);
	player_files = (char **)malloc(sizeof(char *) * g_vm->amount_players);
	i = -1;
	while (++i < g_vm->amount_players)
		player_files[i] = argv[g_vm->plr_nbr[i].index_file];
	if (players_parser(player_files) == -1)
	{
		free_g_players();
		free(player_files);
		return (-1);
	}
	free(player_files);
	g_vm->last_live_player = g_vm->amount_players;
	return (1);
}
