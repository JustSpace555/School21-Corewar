/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:25:49 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 15:25:50 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_free_and_error(t_asm *assm, char *str, char *error)
{
	free(str);
	ft_free_asm(assm);
	ft_str_errout(error);
}

void	ft_free_asm(t_asm *assm)
{
	int i;

	i = 0;
	if (assm->file != NULL)
		ft_free_mas_strings(assm->file);
	if (assm->instr != NULL)
	{
		while (i < assm->count_lines)
		{
			if (assm->instr[i].label != NULL)
				ft_strdel(&assm->instr[i].label);
			if (assm->instr[i].args[0] != NULL)
				ft_strdel(&assm->instr[i].args[0]);
			if (assm->instr[i].args[1] != NULL)
				ft_strdel(&assm->instr[i].args[1]);
			if (assm->instr[i].args[2] != NULL)
				ft_strdel(&assm->instr[i].args[2]);
			i++;
		}
		free(assm->instr);
	}
	if (assm->size_ins != NULL)
		free(assm->size_ins);
}
