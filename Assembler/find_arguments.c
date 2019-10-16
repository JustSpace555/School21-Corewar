/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:24:03 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/29 15:24:04 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_find_first_arg(char *str, t_instr *ins, t_asm *assm)
{
	char	*temp;
	int		i;

	i = 0;
	if (ft_arg_is_reg(str) || ft_arg_is_dir(str) || ft_arg_is_ind(str))
	{
		while (str[i] != '\0' && str[i] != SEPARATOR_CHAR
			&& !ft_is_space_symb(str[i]))
			i++;
		temp = ft_strsub(str, i, ft_strlen(str) - i);
		ins->args[0] = ft_strsub(str, 0, i);
		ft_strdel(&str);
		return (temp);
	}
	else
	{
		free(str);
		ft_free_asm(assm);
		ft_str_errout("Not valid first argument!");
	}
	return (NULL);
}

char	*ft_find_second_arg(char *str, t_instr *ins, t_asm *assm)
{
	char	*temp;
	int		i;

	i = 0;
	if (ft_arg_is_reg(str) || ft_arg_is_dir(str) || ft_arg_is_ind(str))
	{
		while (str[i] != '\0' && str[i] != SEPARATOR_CHAR
			&& !ft_is_space_symb(str[i]))
			i++;
		temp = ft_strsub(str, i, ft_strlen(str) - i);
		ins->args[1] = ft_strsub(str, 0, i);
		ft_strdel(&str);
		return (temp);
	}
	else
	{
		free(str);
		ft_free_asm(assm);
		ft_str_errout("Not valid second argument!");
	}
	return (NULL);
}

char	*ft_find_third_arg(char *str, t_instr *ins, t_asm *assm)
{
	char	*temp;
	int		i;

	i = 0;
	if (ft_arg_is_reg(str) || ft_arg_is_dir(str) || ft_arg_is_ind(str))
	{
		while (str[i] != '\0' && str[i] != SEPARATOR_CHAR
			&& !ft_is_space_symb(str[i]))
			i++;
		temp = ft_strsub(str, i, ft_strlen(str) - i);
		ins->args[2] = ft_strsub(str, 0, i);
		ft_strdel(&str);
		return (temp);
	}
	else
	{
		free(str);
		ft_free_asm(assm);
		ft_str_errout("Not valid third argument!");
	}
	return (NULL);
}

void	ft_not_valid_arg3(char *substr, t_asm *assm)
{
	ft_strdel(&substr);
	ft_free_asm(assm);
	ft_str_errout("Not valid third argument!");
}

void	ft_find_args(char *str, t_instr *ins, t_asm *assm)
{
	char	*substr;

	substr = ft_find_first_arg(str, ins, assm);
	substr = ft_sub_unnecess(substr);
	if (substr[0] == '\0')
	{
		ft_strdel(&substr);
		return ;
	}
	substr = ft_find_second_arg(substr, ins, assm);
	substr = ft_sub_unnecess(substr);
	if (substr[0] == '\0')
	{
		ft_strdel(&substr);
		return ;
	}
	substr = ft_find_third_arg(substr, ins, assm);
	substr = ft_sub_unnecess_arg3(substr);
	if (substr[0] == '\0')
	{
		ft_strdel(&substr);
		return ;
	}
	else
		ft_not_valid_arg3(substr, assm);
}
