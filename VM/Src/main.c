/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:19 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/14 13:05:20 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

int		main(int argc, char *argv[])
{
	if (argc < 2)
	{
		print_usage();
		return (-1);
	}
	else
	{
		initialize_vm();
<<<<<<< HEAD
		if (parsing(argc, argv) == -1)
			return (-1);	
=======
		if (!parsing(argc, argv))
			return (-1);
>>>>>>> f27f35fcf2e6a1ef39b15068ddaf4073c6f561ca
		virtual_machine();
	}
	return (1);
}
