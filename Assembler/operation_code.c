/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:11:34 by eskeleto          #+#    #+#             */
/*   Updated: 2019/10/16 16:23:51 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_not_valid_operation(t_asm *assm)
{
	ft_free_asm(assm);
	ft_str_errout("Not valid operation!");
}

char	*ft_sub_operation(char *str, int next)
{
	char	*temp;
	int		i;

	i = next;
	ft_skip_spaces(str, &i);
	temp = ft_strsub(str, i, ft_strlen(str) - i);
	free(str);
	return (temp);
}

void	ft_set_opcode(t_instr *ins, t_oper *oper, char *str_oper, int i)
{
	ins->opcode = oper[i].code;
	free(str_oper);
}

char	*ft_find_opcode(char *str, t_instr *ins, t_oper *oper, t_asm *assm)
{
	int		i;
	int		next;
	char	*str_oper;

	i = 0;
	while (i < 16)
	{
		next = ft_strlen(oper[i].name);
		if (next <= (int)ft_strlen(str))
		{
			str_oper = ft_strsub(str, 0, next);
			if (ft_strequ(str_oper, oper[i].name) && (str[next] == '-'
				|| ft_is_space_symb(str[next]) || str[next] == DIRECT_CHAR))
			{
				ft_set_opcode(ins, oper, str_oper, i);
				return (ft_sub_operation(str, next));
			}
			free(str_oper);
		}
		else
			ft_not_valid_operation(assm);
		i++;
	}
	ft_not_valid_operation(assm);
	return (NULL);
}
