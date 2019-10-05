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
# define BATTLEFIELD_CELL(i, j, l_c) g_battlefield[i + j + l_c]
# define GET_CUR_POS_BYTE(cursor, extra) GET_BYTE((*cursor)->cur_pos + extra)
# define GET_REG_VALUE(cursor, reg_i) cursor->reg[reg_i]
# define CODE_PER_LINE 64 // change to 32

# define CURRENT_CYCLE g_main_info[0]
# define CTD g_main_info[1]
# define LAST_CYCLE_CHECK g_main_info[2]
# define AMOUNT_CHECKS g_main_info[3]
# define VIS_QUIT g_main_info[4]
# define VIS_PAUSE g_main_info[5]

# define CHECK_EXEC(cursor) if (check_for_cycle_exec(*cursor) == -1) return ;

/*
**		c = cursor
**		r = register
**		l = label size (4 or 2)
**		b = byte val (1 or 0)
**		n = amount_arguments
*/
# define CHECK_REG(c,r,l,b,n) if(r>REG_NUMBER||r==0){move_cursor(*c,l,b,n);return;}

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
	int				ver;
	int				last_live_player;
	int				*order_idtfrs;
	int				amount_players;
	t_plr_nbr		*plr_nbr;
}					t_vm;

typedef struct		s_cursor
{
	unsigned int	player_id;
	unsigned int	cursror_id;
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
	char			*aff_out;
	int				code_size;
	char			*code;
	int				last_alive;
	int				nbr_live;
	int				amount_cursors;
	t_bool			is_alive;
}					t_player;

typedef struct		s_battlefield
{
	unsigned char	code;
	char			color;
	int				color_r;
	int				color_g;
	int				color_b;
	int				write_cycles;
	t_bool			cursor;
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
**					[0] = (int)current_cycle
**					[1] = (int)cycle_to_die
**					[2] = (int)last_cycle_check
**					[3] = (int)amount_checks
**					[4] = (int)quit
**					[5] = (int)pause
*/
int					g_main_info[6];
t_vm				*g_vm;

/*
**					Print
*/

void				print_hex_data(char *file);
void				show_bin_int(unsigned int i);
void				show_bin_char(unsigned char c);
void				print_players(void);
void				print_battlefield(void);
void				print_usage(void);

/*
**					Initialize
*/

void				initialize_vm(void);
void				initialize_battlefield(void);
void				initialize_cursors(void);
void				initialize_g_players(void);
void				initialise_main_info(t_cycles_to_die *repeate);

/*
**					Help
*/

int					make_4_byte_int(u_int8_t buffer[4]);
void				copy_bytes_to_string(char **str, u_int8_t buffer[4],
						int amount_of_bytes, int code_size);
int					check_for_header(u_int8_t buffer[4]);
int					get_code_size(u_int8_t buffer[4]);
int					ft_is_strdigit(char *str);
void				free_g_players(void);
void				choose_color(t_battlefield *cell, int i);
int					choose_reverse_color(t_battlefield *cell);
char				choose_color_char(int i);
void				check_alive_cursors(void);
void				free_all(void);
void				push_winner_terminal(void);
void				push_winner(t_cycles_to_die repeate);

/*
**					Main funcions
*/

void				virtual_machine(void);
int					players_parser(char **files_champions);
int					parsing_arguments(int argc, char **argv, t_vm *vm);

/*
**					Operations
*/

void				live(t_cursor *cursor);
void				ld(t_cursor *cursor);
void				st(t_cursor	*cursor);
void				add(t_cursor *cursor);
void				sub(t_cursor *cursor);
void				and(t_cursor *cursor);
void				or(t_cursor *cursor);
void				xor(t_cursor *cursor);
void				zjmp(t_cursor *cursor);
void				sti(t_cursor *cursor);
void				ldi(t_cursor *cursor);
void				lldi(t_cursor *cursor);
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
									int label_size, int amount_arguments);
short				get_short_data(short addres);
unsigned int		get_int_data(short addres);
unsigned int		get_first_arg(t_cursor *cursor, unsigned char codage, int label_size, unsigned short *offset);
unsigned int		get_second_arg(t_cursor *cursor, unsigned char codage, int label_size, unsigned short *offset);
unsigned int		get_third_arg(t_cursor *cursor, unsigned char codage, int label_size, unsigned short *offset);
void				move_cursor(t_cursor *cursor, int label_size, int byte_val, int amount_arguments);
void				write_amount_of_bytes_data(short addres, void *write, int size_of_write, char color);
void				make_one_new_cursor(t_cursor cursor);
void				print_sti(t_cursor *cursor, int reg, int sec_arg, int third_arg);

#endif
