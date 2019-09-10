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
# define CODE_PER_LINE 64

typedef enum
{
	false,
	true
}					t_bool;

typedef struct		s_player_nbr
{
	int				index_file;
	int				identifier;
}					t_plr_nbr;

typedef struct		s_vm
{
	int				dump;
	int				vis;
	int				*order_idtfrs;
	int				amount_players;
	t_plr_nbr		*plr_nbr;
}					t_vm;

typedef struct		s_cursor
{
	int 			id;
	t_bool			carry;
	uint8_t			operation_code;
	unsigned int	reg[REG_NUMBER];
	int				last_alive;
	int 			cycle_exec;
	int 			cur_pos;
	int 			bytes_to_next_op;
}					t_cursor;

typedef struct		s_player
{
	int				start_position;
	int				identifier;
	char			*name;
	char			*comment;
	int				code_size;
	char			*code;
}					t_player;

typedef struct		s_battlefield
{
	unsigned char	code;
	char			color;
	t_bool			coach;
}					t_battlefield;

t_player			*g_players;
t_battlefield		*g_battlefield;
t_cursor			*g_cursor;


/*
**					Print
*/

void				print_hex_data(char *file);
void				show_bin_int(unsigned int i);
void				show_bin_char(unsigned char c);
void				print_players(int amount_players);
void				print_battlefield(void);


/*
**					Initialize
*/

void				initialize_vm(t_vm *vm);
void				initialize_battlefield(void);
void				initialize_cursor(int amount_players);
void				initialize_g_players(int amount_players);

/*
**					Help
*/

int					make_4_byte_int(u_int8_t buffer[4]);
void				copy_bytes_to_string(char **str, u_int8_t buffer[4], int amount_of_bytes);
int					check_for_header(u_int8_t buffer[4]);
int					get_code_size(u_int8_t buffer[4]);
int					ft_is_strdigit(char *str);
void				free_g_players(int amount_players);
char				choose_color(int i);

/*
**					Main funcions
*/

void				virtual_machine(t_vm *vm);
int					players_parser(int amount_players, char **files_champions, t_vm vm);
int					parsing_arguments(int argc, char **argv, t_vm *flags);

#endif