/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:05:02 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/24 13:12:04 by rdelicad         ###   ########.fr       */
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
		printf("%s\n", help[i]);
}

static int	setup_handler(t_args *args, int ac, char **av)
{
	if (geteuid() != 0) {
		printf("ft_ping: This program must be run as root (RAW socket required)\n");
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
	
	/* Debug: mostrar información resuelta */
	if (args.hostname)
		printf("traceroute to %s (%s)\n", args.hostname, args.dest_ip);
	else
		printf("traceroute to %s\n", args.dest_ip);
	
	return (0);
}