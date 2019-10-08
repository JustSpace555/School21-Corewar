#include "../Headers/virtual_header.h"

int		main(int argc, char *argv[])
{
	if (argc < 2)
	{
		print_usage();
		return (0);
	}
	else
	{
		initialize_vm();
		if (!parsing(argc, argv))
			return (0);
		virtual_machine();
	}
	return (1);
}
