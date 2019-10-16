/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:40:51 by eskeleto          #+#    #+#             */
/*   Updated: 2019/09/10 13:40:52 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include "op.h"
# include "libft.h"

# define BUFF_SIZE 32
# define COUNT_ARG 3
# define MAX_FD 4096

typedef struct		s_oper
{
	char			*name;
	int				code;
	int				narg;
	unsigned int	type_arg[COUNT_ARG];
	int				is_code_arg;
	int				size_t_dir;
}					t_oper;

typedef struct		s_instr
{
	char			*label;
	int				opcode;
	char			*args[COUNT_ARG];
}					t_instr;

typedef struct		s_asm
{
	t_header		header;
	int				count_lines;
	int				newlines;
	char			**file;
	t_instr			*instr;
	int				*size_ins;
}					t_asm;

int					get_next_line(const int fd, char **line);
char				**ft_get_file(int fd, int count);
void				ft_counts_line_file(int fd, t_asm *assm);
void				ft_init_asm(t_asm *assm);
void				ft_free_asm(t_asm *assm);
void				ft_init_instructions(t_asm *assm);
void				ft_init_instr(t_instr *instr);
t_oper				*ft_init_oper();
char				*ft_find_label(char *str, t_instr *ins);
void				ft_skip_spaces(char *str, int *i);
int					ft_only_label(char **str, t_instr *ins);
char				*ft_find_opcode(char *str, t_instr *ins,
		t_oper *oper, t_asm *assm);
void				ft_not_valid_operation(t_asm *assm);
int					ft_arg_is_reg(char *str);
int					ft_arg_is_ind(char *str);
int					ft_arg_is_dir(char *str);
char				*ft_sub_unnecess(char *str);
char				*ft_sub_unnecess_arg3(char *str);
void				ft_find_args(char *str, t_instr *ins, t_asm *assm);
void				ft_check_counts_args(t_asm *assm, t_instr *ins,
		t_oper *oper);
void				ft_check_arg_and_type(t_asm *assm, t_instr *ins,
		t_oper *oper);
void				ft_check_file(t_asm *assm, t_oper *oper);
void				ft_size_instructions(t_asm *assm, t_oper *oper);
t_oper				ft_get_oper(t_oper *oper, t_instr ins);
unsigned int		ft_reverse_four_byte(unsigned int x);
unsigned short		ft_reverse_two_byte(unsigned int x);
void				ft_header_to_bytes(t_asm *assm, int fd);
void				ft_args_to_bytes(t_asm *assm, int fd, t_instr ins, int i);
void				ft_number_to_bytes(int fd, int byte, t_instr ins);
void				ft_number_to_two_bytes(int fd, int byte);
void				ft_in_bytes(t_asm *assm, int fd);
void				ft_str_errout(char *str);
void				ft_check_register(t_asm *assm, t_instr ins);
void				ft_find_name_and_comment(int fd, t_asm *assm);
void				ft_skip_spaces_and_newline(char *allfile, t_asm *assm,
		int *i);
int					ft_find_name(t_asm *assm, char *name);
void				ft_free_and_error(t_asm *assm, char *str, char *error);
void				ft_check_labels_on_duplicate(t_asm *assm);
void				ft_multiple_files(int argc, char **argv);
void				ft_solution(int fd, char *argv);
int					ft_find_comment(t_asm *assm, char *name);
void				ft_skip_lines(char *allfile, t_asm *assm, int *i);
int					ft_newlines_before_ins(char *allfile, int i);

#endif
