/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_header.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:06:20 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 16:41:25 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define CODE_PER_LINE 64

# define CURRENT_CYCLE g_main_info[0]
# define CTD g_main_info[1]
# define LAST_CYCLE_CHECK g_main_info[2]
# define AMOUNT_CHECKS g_main_info[3]
# define VIS_QUIT g_main_info[4]
# define VIS_PAUSE g_main_info[5]

typedef enum
{
	false,
	true
}	t_bool;

typedef struct				s_player_nbr
{
	int						index_file;
	int						identifier;
}							t_plr_nbr;

typedef struct				s_vm
{
	int						dump;
	int						vis;
	int						ver;
	int						aff;
	int						color_print;
	int						last_live_player;
	int						*order_idtfrs;
	int						amount_players;
	int						cursors_id_iter;
	t_plr_nbr				*plr_nbr;
}							t_vm;

typedef struct				s_cursor
{
	unsigned int			player_id;
	unsigned int			cursror_id;
	t_bool					carry;
	uint8_t					operation_code;
	unsigned int			reg[REG_NUMBER];
	int						last_alive;
	int						cycle_exec;
	unsigned short			cur_pos;
	int						bytes_to_next_op;
	char					color;
}							t_cursor;

typedef struct				s_player
{
	int						start_position;
	unsigned int			identifier;
	char					*file_name;
	char					*name;
	char					*comment;
	char					*aff_out;
	int						code_size;
	char					*code;
	int						last_alive;
	int						nbr_live;
	int						amount_cursors;
	t_bool					is_alive;
}							t_player;

typedef struct				s_battlefield
{
	unsigned char			code;
	char					color;
	int						color_r;
	int						color_g;
	int						color_b;
	int						write_cycles;
	t_bool					cursor;
}							t_battlefield;

typedef struct				s_cyles_to_die
{
	int						num_p_r;
	int						num_r;
	int						amount_of_repeate;
}							t_cycles_to_die;

typedef struct				s_cursors_list
{
	t_cursor				cursor;
	struct s_cursors_list	*next;
}							t_cursors_list;

t_player					*g_players;
t_battlefield				*g_battlefield;
t_cursors_list				*g_cursors;
int							g_cursors_amount;
int							g_amount_live_operations;

/*
**							[0] = (int)current_cycle
**							[1] = (int)cycle_to_die
**							[2] = (int)last_cycle_check
**							[3] = (int)amount_checks
**							[4] = (int)quit
**							[5] = (int)pause
*/
int							g_main_info[6];
t_vm						*g_vm;

/*
**							Main additions
*/

int							check_unattached_index(int index,
											t_plr_nbr *plr_nbr);
int							find_unattached_file(t_vm *vm, char **argv,
																int argc);
void						set_identifiers(t_vm *vm, int argc, char **argv);
int							parsing(int argc, char **argv);

/*
**							Print
*/

void						print_hex_data_help(int count, uint8_t *buffer,
																	int i);
void						print_hex_data(char *file);
void						show_bin_int(unsigned int i);
void						show_bin_char(unsigned char c);
void						print_players(void);
void						print_battlefield_help(int c);
void						print_battlefield(void);
void						print_usage(void);
void						introduce(void);
void						push_vis(t_cycles_to_die repeate, char *status);
void						print_pc_movement(t_cursor *cursor, int skip);

/*
**							Print cursors help
*/
void						print_sti(t_cursor *cursor, int reg,
									int sec_arg, int third_arg);
void						print_ldi(t_cursor *cursor, int f_arg,
											int s_arg, int t_arg);
void						print_lldi(t_cursor *cursor, int f_arg,
											int s_arg, int t_arg);
void						check_and_print_ldi(t_cursor *cursor,
								int f_arg, int s_arg, int t_arg);
void						check_and_print_st(t_cursor *cursor,
											int f_arg, int s_arg);
void						check_and_print_lld(t_cursor *cursor,
											int f_arg, int s_arg);

/*
**							Initialize
*/

void						initialize_vm(void);
void						initialize_battlefield(void);
t_cursors_list				*make_new_cursors_list(void);
void						initialize_cursors(void);
void						initialize_g_players(void);
void						initialise_main_info(t_cycles_to_die *repeate);
void						fill_free_space_battlefield(int *byte, int diff);
void						fill_battlefield(void);
void						initialize_all(t_cycles_to_die *repeate);

/*
**							Help
*/

int							ft_is_strdigit(char *str);
void						choose_color(t_battlefield *cell, int i);
int							choose_reverse_color(t_battlefield *cell);
char						choose_color_char(int i);
void						check_alive_cursors(void);
void						push_winner(t_cycles_to_die repeate);
t_bool						check_reg(unsigned char reg);
int							check_reg_write_arg(t_cursor *cursor,
								unsigned char codage, int *value, int arg_num);
void						exec_operation(t_cursor *cursor);
void						choose_operaion(t_cursor *cursor,
											unsigned char byte);
void						zeroing_nbr_live(void);
void						process_operation(void);
void						vis_and_check(t_cycles_to_die *repeate);
void						vm_check(t_cycles_to_die *repeate);
void						zeroing_cursors_args(int *plr_id);
void						inc_current_cycle_and_print(void);
int							check_flags(int argc, char **ar, int *i);
int							check_file(char *argument);


/*
**							Free memory
*/

void						free_all(void);
void						free_g_players(void);
void						*print_battlefield_and_free(void);

/*
**							Players parser help
*/

int							make_4_byte_int(u_int8_t buffer[4]);
void						copy_bytes_to_string(char *str, u_int8_t buffer[4],
								int amount_of_bytes, int code_size);
int							check_for_header(u_int8_t buffer[4]);
int							get_code_size(u_int8_t buffer[4]);
int							check_fd(int *fd, char *champion_file);
void						initialize_one_g_player(int i);
void						zeroing_string_size(int *string_size,
										int amount_bytes, int *sum);
int							if_header_bytes(int amount_bytes,
											uint8_t buffer[4]);
void						make_g_player_name(int amount_bytes,
								uint8_t buffer[4], int i, int *string_size);
int							make_g_player_size(int amount_bytes,
										uint8_t buffer[4], int i);
void						make_g_player_comment(int amount_bytes,
								uint8_t buffer[4], int i, int *string_size);
void						make_g_player_code(int amount_bytes,
								uint8_t buffer[4], int i, int *string_size);
int							check_for_overflow(void);

/*
**							Main funcions
*/

void						*virtual_machine(void);
int							players_parser(char **files_champions);

/*
**							Operations
*/

void						live(t_cursor *cursor);
void						ld(t_cursor *cursor);
void						st(t_cursor	*cursor);
void						add(t_cursor *cursor);
void						sub(t_cursor *cursor);
void						and(t_cursor *cursor);
void						or(t_cursor *cursor);
void						xor(t_cursor *cursor);
void						zjmp(t_cursor *cursor);
void						sti(t_cursor *cursor);
void						ldi(t_cursor *cursor);
void						lldi(t_cursor *cursor);
void						lld(t_cursor *cursor);

/*
**							selector == 0 -> fork
**							selector != 1 -> lfork
*/
void						fork_lfork(t_cursor *cursor, int selector);
void						aff(t_cursor *cursor);

/*
**							Operations help
*/

int							check_for_cycle_exec(t_cursor *cursor);
int							get_var_byte(unsigned char code, int offset,
														int label_size);
int							get_amount_bytes_to_skip(unsigned char code,
									int label_size, int amount_arguments);
short						get_short_data(short addres);
unsigned int				get_int_data(short addres);
unsigned int				get_first_arg(t_cursor *cursor,
											unsigned char codage,
											int label_size,
											unsigned short *offset);
unsigned int				get_second_arg(t_cursor *cursor,
											unsigned char codage,
											int label_size,
											unsigned short *offset);
unsigned int				get_third_arg(t_cursor *cursor,
											unsigned char codage,
											int label_size,
											unsigned short *offset);
void						jump_to_next_op(t_cursor *cursor,
											unsigned char codage,
											int label_size,
											int amount_arguments);
void						move_cursor(t_cursor *cursor, int skip);
void						write_short_data(short addres,
								short write, char color);
void						write_int_data(short addres,
								unsigned int write, char color);
void						make_one_new_cursor(t_cursor cursor);
short						arena_truncation(short address);

#endif
