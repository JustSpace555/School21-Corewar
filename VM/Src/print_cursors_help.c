#include "../Headers/virtual_header.h"

void	print_sti(t_cursor *cursor, int reg, int sec_arg, int third_arg)
{
	ft_printf("P %4d | sti r%d %d %d\n", cursor->cursror_id,
									reg, sec_arg, third_arg);
	ft_printf("      | -> store to %d + %d = %d (with pc and mod %d)\n",
								sec_arg, third_arg, sec_arg + third_arg,
					cursor->cur_pos + ((sec_arg + third_arg) % IDX_MOD));
}

void	print_ldi(t_cursor *cursor, int f_arg, int s_arg, int t_arg)
{
	ft_printf("P %4d | ldi %d %d r%d\n", cursor->cursror_id,
													f_arg,
													s_arg,
													t_arg);
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
											f_arg,
											s_arg,
											f_arg + s_arg,
											cursor->cur_pos +
											(f_arg + s_arg) % IDX_MOD);
}

void	print_lldi(t_cursor *cursor, int f_arg, int s_arg, int t_arg)
{
	ft_printf("P %4d | lldi %d %d r%d\n", cursor->cursror_id,
													f_arg,
													s_arg,
													t_arg);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
											f_arg,
											s_arg,
											f_arg + s_arg,
											cursor->cur_pos
											+ (f_arg + s_arg));
}

void	check_and_print_ldi(t_cursor *cursor, int f_arg, int s_arg, int t_arg)
{
	if (g_vm->ver == 1)
		print_ldi(cursor, f_arg, s_arg, t_arg);
}
