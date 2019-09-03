#ifndef VIRTUAL_HEADER_H
# define VIRTUAL_HEADER_H

# include "../../libft/Headers/libft.h"
# include "op.h"

# define BYTES_AFTER_HEADER 4
# define BYTES_AFTER_NAME BYTES_AFTER_HEADER + PROG_NAME_LENGTH
# define NULL_BYTES 4
# define BYTES_AFTER_CODE_SIZE BYTES_AFTER_NAME + NULL_BYTES + 4
# define BYTES_AFTER_COMMENT BYTES_AFTER_CODE_SIZE + COMMENT_LENGTH
# define PLAYER(i) g_players[i]

typedef struct	s_player
{
	int			identifier;
	char		*name;
	char		*comment;
	int			code_size;
	char		*code;
}				t_player;

t_player		*g_players;

void	virtual_machine(int amount_players, char **files_champoins);
int		players_parser(int amount_players, char **files_champions);
void	print_hex_data(char *file);
void	print_zero(char *color, uint8_t buffer);
void	show_bin_int(unsigned int i);
void	show_bin_char(unsigned char c);
void	print_players(int amount_players);
int		make_4_byte_int(u_int8_t buffer[4]);
void	copy_bytes_to_string(char **str, u_int8_t buffer[4]);
int		check_for_header(u_int8_t buffer[4]);
int		get_code_size(u_int8_t buffer[4]);

#endif
