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
# define CURSOR(i) g_cursors[i]
# define GET_BYTE(pos) g_battlefield[pos].code
# define GET_CUR_POS_BYTE(cursor, extra) GET_BYTE((*cursor)->cur_pos + extra)
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
	t_bool			is_alive;
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
	t_bool			cursor;
}					t_battlefield;

t_player			*g_players;
t_battlefield		*g_battlefield;
t_cursor			*g_cursors;


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
void				initialize_cursors(int amount_players);
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

/*
**					Operations
*/

void				live(t_cursor *cursor);

void				st(t_cursor	*cursor);

void				sub(t_cursor *cursor);

void				or(t_cursor *cursor);

/*
**					Operations help
*/

int					check_for_cycle_exec(t_cursor *cursor);
int					get_var_byte(unsigned char code, int offset, int label_size);
int					get_amount_bytes_to_skip(unsigned char code, int label_size);
void				*get_amount_of_bytes_data(short addres, int amount_for_read);
void				if_return(t_cursor *cursor, int label_size, int byte_val);
void				move_cursor(t_cursor *cursor, int new_value);
#endif
