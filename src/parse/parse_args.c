/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:37:19 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/25 11:32:09 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	setup_default_values(t_args *args)
{
	args->show_help = 0;
	args->target = NULL;
}

char *get_target_from_args(int ac, char **av)
{
	char *target = NULL;
	int i = 1;

	while (i < ac)
	{
		if (av[i][0] != '-')
		{
			if (target != NULL)
			{
				printf("ft_traceroute: too many destinations\n");
				exit(2);
			}
			target = av[i];
		}
		i++;
	}
	return target;
}

void parse_arguments(t_args *args, int ac, char **av)
{
	char	*target;
	int		i;
	
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
			print_help();
			exit(0);
		}
		i++;
	}

	/* Validar argumentos inválidos que empiecen con - */
	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' && ft_strcmp(av[i], "--help") != 0)
		{
			printf("ft_traceroute: invalid option -- '%s'\n", av[i]);
			printf("Try 'ft_traceroute --help' for more information.\n");
			exit(1);
		}
		i++;
	}
	
	// inicializar args con valores por defecto
	setup_default_values(args);

	// Parsear destino
	target = get_target_from_args(ac, av);
	if (target == NULL && !args->show_help)
	{
		printf("ft_traceroute: usage error: Destination address required\n");
		//print_help();
		exit(2);  // Exit code 2 para falta de destino
	}
	args->target = target;
	validate_destination(args);
}