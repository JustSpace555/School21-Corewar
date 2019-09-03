#ifndef VIRTUAL_HEADER_H
# define VIRTUAL_HEADER_H

# include "../libft/Headers/libft.h"
# include "op.h"

typedef enum
{
	false,
	true
}	t_bool;

typedef struct	s_player
{
	int			identifier;
	char		*name;
	char		*comment;
	int			code_size;
	char		*code;
}				t_player;

typedef struct	s_player_nbr
{
	int 	index_file;
	int 	identifier;
}				t_plr_nbr;

typedef struct	s_vm
{
	int 		dump;
	int 		vis;
	int			*order_idtfrs;
	int 		amount_players;
	t_plr_nbr	*plr_nbr;
}				t_vm;

typedef struct	s_cursor
{
	int 			id;
	t_bool			carry;
	uint8_t			operation_code;
	unsigned int	reg[MAX_ARGS_NUMBER];
	int				last_live;
	int 			cycle_exec;
	int 			cur_pos;
	int 			bytes_to_next_op;

}				t_cursor;

t_player		*g_players;

int		virual_machine(int amount_players, char **files_champoins);
void	print_hex_data(int argc, char **argv);
int		parsing_arguments(int argc, char **argv, t_vm *flags);
void	initialize_vm(t_vm *vm);
int 	ft_is_strdigit(char *str);

#endif
