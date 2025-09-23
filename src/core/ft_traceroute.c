/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:05:02 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/23 17:58:29 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	print_help()
{
	const char	*help[] = {
		"Usage:\n"
		" sudo ./ft_traceroute [options] <destination>",
		"",
		"Options:",
		"   <destination>\t\tThe host to traceroute to",
		"   --help\t\t\tRead this help and exit",
		NULL	
	};
	
	for (int i = 0; help[i]; i++)
		puts(help[i]);
}

static int	setup_handler(int ac, char **av)
{
	if (geteuid() != 0) {
		printf("ft_ping: This program must be run as root (RAW socket required)\n");
		return 1;
	};
	parse_arguments(ac, av);
	return 0;
}

int	main(int ac, char **av)
{
	if (setup_handler(ac, av) != 0)
		return 1;
	(void)av;
	
	return 0;
}