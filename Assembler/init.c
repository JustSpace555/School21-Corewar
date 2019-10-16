/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:28:10 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 15:28:12 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_oper g_op[17] =
{
	{"live", 1, 1, {T_DIR}, 0, 4},
	{"ld", 2, 2, {T_DIR | T_IND, T_REG}, 1, 4},
	{"st", 3, 2, {T_REG, T_IND | T_REG}, 1, 4},
	{"add", 4, 3, {T_REG, T_REG, T_REG}, 1, 4},
	{"sub", 5, 3, {T_REG, T_REG, T_REG}, 1, 4},
	{"and", 6, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"or", 7, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"xor", 8, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"zjmp", 9, 1, {T_DIR}, 0, 2},
	{"ldi", 10, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{"sti", 11, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
	{"fork", 12, 1, {T_DIR}, 0, 2},
	{"lld", 13, 2, {T_DIR | T_IND, T_REG}, 1, 4},
	{"lldi", 14, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{"lfork", 15, 1, {T_DIR}, 0, 2},
	{"aff", 16, 1, {T_REG}, 1, 4},
	{NULL, 0, 0, {0}, 0, 0}
};

t_oper	*ft_init_oper(void)
{
	t_oper *op;

	op = g_op;
	return (op);
}

void	ft_init_asm(t_asm *assm)
{
	assm->header.magic = COREWAR_EXEC_MAGIC;
	assm->header.prog_size = 0;
	assm->count_lines = 0;
	assm->newlines = 0;
	assm->file = NULL;
	assm->instr = NULL;
	assm->size_ins = NULL;
}

void	ft_init_instr(t_instr *instr)
{
	instr->label = NULL;
	instr->args[0] = NULL;
	instr->args[1] = NULL;
	instr->args[2] = NULL;
	instr->opcode = 0;
}

void	ft_init_instructions(t_asm *assm)
{
	int	i;

	i = 0;
	while (i < assm->count_lines)
	{
		assm->instr[i].label = NULL;
		assm->instr[i].args[0] = NULL;
		assm->instr[i].args[1] = NULL;
		assm->instr[i].args[2] = NULL;
		assm->instr[i].opcode = 0;
		i++;
	}
}
