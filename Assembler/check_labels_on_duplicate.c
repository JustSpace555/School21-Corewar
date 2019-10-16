/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_labels_on_duplicate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:46:34 by eskeleto          #+#    #+#             */
/*   Updated: 2019/09/10 13:46:36 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_find_duplicate_label(t_asm *assm, char *label, int i)
{
	int j;

	j = 0;
	while (j < assm->count_lines)
	{
		if ((i != j) && (assm->instr[j].label != NULL))
		{
			if (ft_strequ(assm->instr[j].label, label))
			{
				ft_free_asm(assm);
				ft_str_errout("Duplacate label");
			}
		}
		j++;
	}
}

void	ft_check_labels_on_duplicate(t_asm *assm)
{
	int i;

	i = 0;
	while (i < assm->count_lines)
	{
		if (assm->instr[i].label != NULL)
			ft_find_duplicate_label(assm, assm->instr[i].label, i);
		i++;
	}
}
