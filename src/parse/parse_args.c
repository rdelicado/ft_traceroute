/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:37:19 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/26 10:58:59 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	setup_default_values(t_args *args)
{
	args->show_help = 0;
	args->target = NULL;
	args->max_ttl = 30; // 30 saltos por defecto 
	args->port = 33434; // Puerto UDP por defecto
	args->num_probes = 3; // 3 paquetes por defecto
}

void parse_arguments(t_args *args, int ac, char **av)
{
	int i;
	
	setup_default_values(args);

	if (ac < 2) {
		print_help();
		exit(1);
	}

	i = 1;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "--help") == 0)
		{
			if (ac != 2)
			{
				printf("ft_traceroute: usage error: --help cannot be used with other arguments\n");
				exit(1);
			}
			args->show_help = 1;
			print_help();
			exit(0);
		}
		else if (ft_strcmp(av[i], "-m") == 0)
		{
			if (i + 1 >= ac)
			{
				printf("ft_traceroute: option '-m' requires an argument\n");
				exit(1);
			}
			args->max_ttl = ft_atoi(av[i + 1]);
			i += 2;
			continue;
		}
		else if (ft_strcmp(av[i], "-p") == 0)
		{
			if (i + 1 >= ac)
			{
				printf("ft_traceroute: option '-p' requires an argument\n");
				exit(1);
			}
			args->port = ft_atoi(av[i + 1]);
			if (args->port < 1024 || args->port > 65535)
			{
				printf("ft_traceroute: invalid port '%d'. Must be between 1024 and 65535\n", args->port);
				exit(1);
			}
			if (args->port + args->max_ttl > 65535)
			{
				printf("ft_traceroute: port + max_ttl (%d + %d) exceeds maximum allowed port (65535)\n", args->port, args->max_ttl);
				exit(1);
			}
			i += 2;
			continue;
		}
		else if (ft_strcmp(av[i], "-q") == 0)
		{
			if (i + 1 >= ac)
			{
				printf("ft_traceroute: option 'q' requires an argument\n");
				exit(1);
			}
			args->num_probes = ft_atoi(av[i + 1]);
			if (args->num_probes < 1 || args->num_probes > 10)
			{
				printf("ft_traceroute: invalid number of probes '%d'. Must be between 1 and 10\n", args->num_probes);
				exit(1);
			}
			i += 2;
			continue;
		}
		else if (av[i][0] == '-')
		{
			printf("ft_traceroute: invalid option -- '%s'\n", av[i]);
			printf("Try 'ft_traceroute --help' for more information.\n");
			exit(1);
		}
		else
		{
			// Solo guarda el último argumento como destino
			args->target = av[i];
		}
		i++;
	}

	if (args->target == NULL && !args->show_help)
	{
		printf("ft_traceroute: usage error: Destination address required\n");
		exit(2);
	}

	validate_destination(args);
}