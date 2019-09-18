#ifndef VIRTUAL_HEADER_H
# define VIRTUAL_HEADER_H

# include "../../libft/Headers/libft.h"
# include "../../visualisator/visualisator.h"
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
# define CHECK_EXEC(cursor) if (check_for_cycle_exec(*cursor) == -1) return ;

/*
**		c = cursor
**		r = register
**		l = label size (4 or 2)
**		b = byte val (1 or 0)
*/
# define CHECK_REG(c, r, l, b) if(r > REG_NUMBER){move_cursor(*c,l,b);return;}

/*
**		c = cursor
**		w = cycles to wait
*/
# define CHECK_CYCLES(c, w) if((*c)->cycle_exec == 0) (*c)->cycle_exec = w;

typedef enum
{
	false,
	true
}	t_bool;

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
	unsigned int	id;
	t_bool			carry;
	uint8_t			operation_code;
	unsigned int	reg[REG_NUMBER];
	int				last_alive;
	int				cycle_exec;
	unsigned short	cur_pos;
	int				bytes_to_next_op;
	char			color;
}					t_cursor;

typedef struct		s_player
{
	int				start_position;
	unsigned int	identifier;
	char			*name;
	char			*comment;
	int				code_size;
	char			*code;
	t_bool			is_alive;
}					t_player;

typedef struct		s_battlefield
{
	unsigned char	code;
	char			color;
	t_bool			cursor;
	char			cursor_color;
}					t_battlefield;

typedef struct		s_cyles_to_die
{
	int				num_p_r;
	int				num_r;
	int				amount_of_repeate;
}					t_cycles_to_die;


t_player			*g_players;
t_battlefield		*g_battlefield;
t_cursor			*g_cursors;
int					g_cursors_amount;
int					g_amount_live_operations;

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
void				copy_bytes_to_string(char **str, u_int8_t buffer[4],
										int amount_of_bytes);
int					check_for_header(u_int8_t buffer[4]);
int					get_code_size(u_int8_t buffer[4]);
int					ft_is_strdigit(char *str);
void				free_g_players(int amount_players);
char				choose_color(int i);

/*
**					Main funcions
*/

void				virtual_machine(t_vm *vm);
int					players_parser(int amount_players,
									char **files_champions, t_vm vm);
int					parsing_arguments(int argc, char **argv, t_vm *flags);

/*
**					Operations
*/

void				live(t_cursor *cursor, int cycle);
void				ld(t_cursor *cursor);
void				st(t_cursor	*cursor);
void				add(t_cursor *cursor);
void				sub(t_cursor *cursor);

/*
**					selector == 0 -> and
**					selector == 1 -> or
**					selector >= 2 -> xor
*/
void				and_or_xor(t_cursor *cursor, int selector);
void				zjmp(t_cursor *cursor);
void				sti(t_cursor *cursor);

/*
**					selector == 0 -> ldi
**					selector != 0 -> lldi
*/
void				ldi_lldi(t_cursor *cursor, int selector);

void				lld(t_cursor *cursor);

/*
**					selector == 0 -> fork
**					selector != 1 -> lfork
*/
void				fork_lfork(t_cursor *cursor, int selector);
void				aff(t_cursor *cursor);

/*
**					Operations help
*/

int					check_for_cycle_exec(t_cursor *cursor);
int					get_var_byte(unsigned char code, int offset,
									int label_size);
int					get_amount_bytes_to_skip(unsigned char code,
												int label_size);
short				get_short_data(short addres);
unsigned int		get_int_data(short addres);
void				move_cursor(t_cursor *cursor, int label_size, int byte_val);
void				write_amount_of_bytes_data(short addres, void *write, int size_of_write, char color);
void				make_one_new_cursor(t_cursor cursor);
#endif
