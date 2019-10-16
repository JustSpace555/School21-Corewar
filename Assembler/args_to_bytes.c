/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_to_bytes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:16:41 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 15:16:43 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_reg_to_bytes(int fd, char *reg)
{
	char			*num;
	int				number;
	unsigned int	byte;

	num = ft_strsub(reg, 1, ft_strlen(reg) - 1);
	number = ft_atoi(num);
	byte = (unsigned int)number;
	write(fd, &byte, 1);
	free(num);
}

int		ft_dir_label_to_bytes(t_asm *assm, char *dir, int i)
{
	int j;
	int byte;

	j = i;
	byte = 0;
	while (j < assm->count_lines)
	{
		if (ft_strequ(assm->instr[j].label, dir))
			return (byte);
		byte += assm->size_ins[j];
		j++;
	}
	j = i - 1;
	byte = 0;
	while (j >= 0)
	{
		byte -= assm->size_ins[j];
		if (ft_strequ(assm->instr[j].label, dir))
			return (byte);
		j--;
	}
	return (byte);
}

void	ft_dir_to_bytes(t_asm *assm, int fd, char *dir, int i)
{
	char	*label;
	int		byte;

	if (dir[1] == LABEL_CHAR)
	{
		label = ft_strsub(dir, 2, ft_strlen(dir) - 2);
		byte = ft_dir_label_to_bytes(assm, label, i);
	}
	else
	{
		label = ft_strsub(dir, 1, ft_strlen(dir) - 1);
		byte = ft_atoi(label);
	}
	free(label);
	ft_number_to_bytes(fd, byte, assm->instr[i]);
}

void	ft_ind_to_bytes(t_asm *assm, int fd, char *dir, int i)
{
	char	*label;
	int		byte;

	if (dir[0] == LABEL_CHAR)
	{
		label = ft_strsub(dir, 1, ft_strlen(dir) - 1);
		byte = ft_dir_label_to_bytes(assm, label, i);
	}
	else
	{
		label = ft_strdup(dir);
		byte = ft_atoi(label);
	}
	free(label);
	ft_number_to_two_bytes(fd, byte);
}

void	ft_args_to_bytes(t_asm *assm, int fd, t_instr ins, int i)
{
	int		j;

	j = 0;
	while (j < COUNT_ARG)
	{
		if (ins.args[j] == NULL)
			return ;
		else if (ft_arg_is_reg(ins.args[j]))
			ft_reg_to_bytes(fd, ins.args[j]);
		else if (ft_arg_is_dir(ins.args[j]))
			ft_dir_to_bytes(assm, fd, ins.args[j], i);
		else
			ft_ind_to_bytes(assm, fd, ins.args[j], i);
		j++;
	}
}
