/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_to_bytes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:34:30 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 15:34:32 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_code_type_operation_to_bytes(int fd, t_oper cur_oper, t_instr ins)
{
	int		i;
	size_t	bits;
	size_t	code_of_types;

	i = 0;
	code_of_types = 0;
	if (cur_oper.is_code_arg)
	{
		while (i < COUNT_ARG)
		{
			if (ins.args[i] == NULL)
				bits = 0;
			else if (ft_arg_is_reg(ins.args[i]))
				bits = REG_CODE;
			else if (ft_arg_is_ind(ins.args[i]))
				bits = IND_CODE;
			else
				bits = DIR_CODE;
			code_of_types = code_of_types | bits;
			code_of_types = code_of_types << 2;
			i++;
		}
		write(fd, &code_of_types, 1);
	}
}

void	ft_command_bytes(t_asm *assm, int fd, t_instr ins, int i)
{
	t_oper cur_oper;
	t_oper *oper;

	oper = ft_init_oper();
	if (ins.opcode != 0)
	{
		write(fd, &ins.opcode, 1);
		cur_oper = ft_get_oper(oper, ins);
		ft_code_type_operation_to_bytes(fd, cur_oper, ins);
		ft_args_to_bytes(assm, fd, ins, i);
	}
}

void	ft_in_bytes(t_asm *assm, int fd)
{
	int i;

	i = 0;
	while (i < assm->count_lines)
	{
		ft_command_bytes(assm, fd, assm->instr[i], i);
		i++;
	}
}
