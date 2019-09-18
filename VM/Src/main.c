#include "../Headers/virtual_header.h"

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

int 	find_unattached_file(t_vm *vm, char **argv, int argc)
{
	static int i = 0;

	while (++i < argc)
	{
		if (ft_strstr(argv[i], ".cor") && check_unattached_index(i, vm->plr_nbr))
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

void	print_usage(void)
{
	ft_printf("Usage: ./corewar [-dump N -v -n N] <filename.cor> ...\n");
	ft_printf("\t-dump N\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t-n N\t: set the champion number\n");
	ft_printf("\t-v\t\t: visual mode\n");
}
int		main(int argc, char *argv[])
{
	t_vm		vm;
	char		**player_files;
	int 		i;

	if (argc < 2)
	{
		print_usage();
		return (1);
	}
	else
	{
		initialize_vm(&vm);
		if (parsing_arguments(argc, argv, &vm) == -1)
			return (1);
		if (vm.amount_players > MAX_PLAYERS)
		{
			write(1, "Too many champions\n", 19);
			return (2);
		}
		set_identifiers(&vm, argc, argv);
		player_files = (char **)malloc(sizeof(char *) * vm.amount_players);
		i = -1;
		while (++i < vm.amount_players)
			player_files[i] = argv[vm.plr_nbr[i].index_file];
		if (players_parser(vm.amount_players, player_files, vm) == -1)
		{
			free_g_players(vm.amount_players);
			return (0);
		}
		virtual_machine(&vm);
	}
	return (0);
}
