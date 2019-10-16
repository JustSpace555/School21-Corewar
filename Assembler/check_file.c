/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:21:44 by eskeleto          #+#    #+#             */
/*   Updated: 2019/10/16 15:58:11 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_instr	ft_parse_instruction(t_asm *assm, char *str, t_oper *oper)
{
	t_instr	ins;
	char	*substr;

	ft_init_instr(&ins);
	substr = ft_find_label(str, &ins);
	if (ft_only_label(&substr, &ins))
	{
		free(substr);
		return (ins);
	}
	substr = ft_find_opcode(substr, &ins, oper, assm);
	if (substr[0] == '\0')
	{
		free(substr);
		ft_not_valid_operation(assm);
	}
	ft_find_args(substr, &ins, assm);
	return (ins);
}

void	ft_check_instructions(t_asm *assm, t_oper *oper)
{
	int i;

	i = 0;
	if (!(assm->instr = (t_instr*)malloc(sizeof(t_instr)
			* (assm->count_lines + 1))))
		ft_error();
	ft_init_instructions(assm);
	while (assm->file[i] != NULL)
	{
		assm->instr[i] = ft_parse_instruction(assm, assm->file[i], oper);
		ft_check_register(assm->instr[i]);
		ft_check_counts_args(assm, &assm->instr[i], oper);
		ft_check_arg_and_type(assm, &assm->instr[i], oper);
		i++;
	}
}

void	ft_compare_label(t_asm *assm, char *arg)
{
	int		i;
	char	*str;

	i = 0;
	if (arg[0] == LABEL_CHAR)
		str = ft_strsub(arg, 1, ft_strlen(arg) - 1);
	else
		str = ft_strsub(arg, 2, ft_strlen(arg) - 2);
	while (assm->file[i] != NULL)
	{
		if (ft_strequ(str, assm->instr[i].label))
		{
			free(str);
			return ;
		}
		i++;
	}
	free(str);
	ft_free_asm(assm);
	ft_str_errout("Not valid label in arguments!");
}

void	ft_check_labels(t_asm *assm)
{
	int i;
	int j;

	i = 0;
	while (assm->file[i] != NULL)
	{
		j = 0;
		while (j < 3)
		{
			if (assm->instr[i].args[j] != NULL)
			{
				if (ft_strlen(assm->instr[i].args[j]) >= 2 &&
					(assm->instr[i].args[j][0] == LABEL_CHAR
					|| assm->instr[i].args[j][1] == LABEL_CHAR))
				{
					ft_compare_label(assm, assm->instr[i].args[j]);
				}
			}
			j++;
		}
		i++;
	}
}

void	ft_check_file(t_asm *assm, t_oper *oper)
{
	ft_check_instructions(assm, oper);
	ft_check_labels_on_duplicate(assm);
	ft_check_labels(assm);
}
