/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:19:01 by eskeleto          #+#    #+#             */
/*   Updated: 2019/10/16 15:57:16 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_check_counts_args(t_asm *assm, t_instr *ins, t_oper *oper)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (oper[i].code == ins->opcode)
		{
			if (!((oper[i].narg == 1 && ins->args[0] != NULL
				&& ins->args[1] == NULL && ins->args[2] == NULL)
				|| (oper[i].narg == 2 && ins->args[0] != NULL
				&& ins->args[1] != NULL && ins->args[2] == NULL)
				|| (oper[i].narg == 3 && ins->args[0] != NULL
				&& ins->args[1] != NULL && ins->args[2] != NULL)))
			{
				ft_free_asm(assm);
				ft_str_errout("Not valid counts of arguments!");
			}
		}
		i++;
	}
}

unsigned int	ft_type_argument(char *arg)
{
	if (ft_arg_is_reg(arg))
		return (T_REG);
	else if (ft_arg_is_dir(arg))
		return (T_DIR);
	else if (ft_arg_is_ind(arg))
		return (T_IND);
	return (0);
}

void			ft_check_arg_and_type(t_asm *assm, t_instr *ins, t_oper *oper)
{
	int				i;
	int				j;
	unsigned int	type;
	unsigned int	need_type;

	i = 0;
	while (i < 16)
	{
		j = 0;
		if (oper[i].code == ins->opcode)
		{
			while (j < oper[i].narg)
			{
				type = ft_type_argument(ins->args[j]);
				need_type = oper[i].type_arg[j];
				if ((type & need_type) == 0)
				{
					ft_free_asm(assm);
					ft_str_errout("Not valid type of arguments!");
				}
				j++;
			}
		}
		i++;
	}
}

void			ft_check_register(t_instr ins)
{
	int		i;
	char	*numb;
	int		reg;

	i = 0;
	while (i < COUNT_ARG)
	{
		if (ins.args[i] != NULL)
		{
			if (ft_arg_is_reg(ins.args[i]))
			{
				numb = ft_strsub(ins.args[i], 1, ft_strlen(ins.args[i]) - 1);
				reg = ft_atoi(numb);
				free(numb);
			}
		}
		i++;
	}
}
