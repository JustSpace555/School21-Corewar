/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:18:59 by eskeleto          #+#    #+#             */
/*   Updated: 2019/09/10 14:19:00 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		*ft_init_size_ins(int count)
{
	int *size;

	if (!(size = (int*)malloc(sizeof(int) * (count + 1))))
		ft_error();
	return (size);
}

t_oper	ft_get_oper(t_oper *oper, t_instr ins)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ins.opcode == oper[i].code)
			return (oper[i]);
		i++;
	}
	return (oper[i]);
}

int		ft_calc_size_ins(t_oper *oper, t_instr ins)
{
	int		size;
	t_oper	cur_oper;
	int		i;

	i = 0;
	size = 1;
	cur_oper = ft_get_oper(oper, ins);
	size += cur_oper.is_code_arg;
	while (i < cur_oper.narg)
	{
		if (ins.args[i][0] == 'r')
			size++;
		else if (ins.args[i][0] == DIRECT_CHAR)
			size += cur_oper.size_t_dir;
		else
			size += 2;
		i++;
	}
	return (size);
}

void	ft_size_instructions(t_asm *assm, t_oper *oper)
{
	int i;

	i = 0;
	assm->size_ins = ft_init_size_ins(assm->count_lines);
	while (i < assm->count_lines)
	{
		if (assm->instr[i].opcode == 0)
			assm->size_ins[i] = 0;
		else
			assm->size_ins[i] = ft_calc_size_ins(oper, assm->instr[i]);
		assm->header.prog_size += assm->size_ins[i];
		i++;
	}
}
