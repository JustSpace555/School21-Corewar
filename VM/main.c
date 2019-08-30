/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 15:47:15 by cheller           #+#    #+#             */
/*   Updated: 2019/08/30 16:01:01 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_header.h"

int		main(int argc, char *argv[])
{
	if (argc > MAX_PLAYERS + 1)
	{
		write(1, "Too many champions\n", 19);
		return (2);
	}
	if (argc < 2)
	{
		//usage
		return (1);
	}
	else
	{
		virual_machine(argc, argv);
	}
	return (0);
}
