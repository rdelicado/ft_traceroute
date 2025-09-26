/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:37:19 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/26 09:25:26 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	setup_default_values(t_args *args)
{
	args->show_help = 0;
	args->target = NULL;
	args->max_ttl = 30; // 30 saltos por defecto
}

void parse_arguments(t_args *args, int ac, char **av)
{
	int		i;
	int		dest_count = 0;

	// inicializar args con valores por defecto
	setup_default_values(args);
	
	// si no hay destino
	if (ac < 2) {
		print_help();
		exit(1);
	}

	// si es la ayuda
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
		else  if (ft_strcmp(av[i], "-m") == 0)
		{
			if (i + 1 >= ac)
			{
				printf("ft_traceroute: option '-m' requires an argument\n");
				exit(1);
			}
			args->max_ttl = ft_atoi(av[i + 1]);
			i++; // saltar valor de la flag
		}
		else if (av[i][0] == '-')
		{
			printf("ft_traceroute: invalid option -- '%s'\n", av[i]);
			printf("Try 'ft_traceroute --help' for more information.\n");
			exit(1);
		}
		else
		{
			if (args->target != NULL)
			{
				printf("ft_traceroute: too many destinations\n");
				exit(2);
			}
			args->target = av[i];
			dest_count++;
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