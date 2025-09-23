/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:37:19 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/23 17:50:47 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void parse_arguments(int ac, char **av)
{
	// si no hay destino
	if (ac < 2) {
		printf("ft_ping: usage error: Destination address required\n");
		exit(1);
	}

	// si es la ayuda
	if (ac == 2 && strcmp(av[1], "--help") == 0) {
		print_help();
		exit(0);
	}
	(void)av;
}