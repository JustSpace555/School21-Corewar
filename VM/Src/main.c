#include "../Headers/virtual_header.h"

int		main(int argc, char *argv[])
{
	char		**player_files;

	if (argc < 2)
	{
		print_usage();
		return (0);
	}
	else
	{
		initialize_vm();
		if (!parsing(argc, argv, player_files))
		{
			free_player_files(player_files);
			return (0);
		}
		virtual_machine();
	}
	return (1);
}
