#include "virtual_header.h"

int 	check_unattached_index(int index, t_plr_nbr *plr_nbr)
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

int 	find_unattached_file(t_vm *flags, char **argv, int argc)
{
	static int i = 0;

	while (++i < argc)
	{
		if (ft_strstr(argv[i], ".cor") && check_unattached_index(i, flags->plr_nbr))
			return (i);
	}
	return (0);
}

void	set_identifiers(t_vm *flags, int argc, char **argv)
{
	int i;

	i = -1;
	while (++i < flags->amount_players)
	{
		if (flags->order_idtfrs[i] == 0)
		{
			flags->plr_nbr[i].index_file = find_unattached_file(flags, argv, argc);
			flags->plr_nbr[i].identifier = i + 1;
		}
	}
}

int		main(int argc, char *argv[])
{
	t_vm		vm;
	char		**player_files;
	int 		i;

	if (argc < 2)
	{
		//usage
		return (1);
	}
	else
	{
		initialize_vm(&vm);
		parsing_arguments(argc, argv, &vm);
		if (vm.amount_players > MAX_PLAYERS)
		{
			write(1, "Too many champions\n", 19);
			return (2);
		}
		set_identifiers(&vm, argc, argv);
		player_files = (char**)malloc(sizeof(char*) * vm.amount_players);
		i = -1;
		while (++i < vm.amount_players)
			player_files[i] = argv[vm.plr_nbr[i].index_file];
		//virual_machine(argc, argv);
		free(vm.plr_nbr);
		free(vm.order_idtfrs);
		free(player_files);
	}
	return (0);
}
