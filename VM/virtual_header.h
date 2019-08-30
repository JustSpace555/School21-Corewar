#ifndef VIRTUAL_HEADER_H
# define VIRTUAL_HEADER_H

# include "../libft/Headers/libft.h"
# include "op.h"

# define BYTES_AFTER_HEADER 4
# define BYTES_AFTER_NAME BYTES_AFTER_HEADER + PROG_NAME_LENGTH
# define NULL_BYTES 4
# define BYTES_AFTER_CODE_SIZE BYTES_AFTER_NAME + NULL_BYTES + 4
# define BYTES_AFTER_COMMENT BYTES_AFTER_CODE_SIZE + COMMENT_LENGTH

typedef struct	s_player
{
	int			identifier;
	char		*name;
	char		*comment;
	int			code_size;
	char		*code;
}				t_player;

t_player		*g_players;

int		virual_machine(int amount_players, char **files_champoins);
void	print_hex_data(char *file);

#endif
