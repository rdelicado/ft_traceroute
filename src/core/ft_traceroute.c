/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:05:02 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/26 09:40:03 by rdelicad         ###   ########.fr       */
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
		"   -p <port>\t\tSet the base UDP destination port (default 33434)",
		"   -m <max_ttl>\t\tSet the max number of hops (max TTL to be reached). Default is 30",
		NULL	
	};
	
	for (int i = 0; help[i]; i++)
		printf("%s\n", help[i]);
}

static int	setup_handler(t_args *args, int ac, char **av)
{
	if (geteuid() != 0) {
		printf("ft_traceorute: This program must be run as root (RAW socket required)\n");
		return 1;
	};
	parse_arguments(args, ac, av);
	return 0;
}

int	main(int ac, char **av)
{
	t_args	args;
	
	if (setup_handler(&args, ac, av) != 0)
		return (1);

	if (!convert_ip_binary(&args))
		exit(2);
			
	run_traceroute(&args);
	
	return (0);
}