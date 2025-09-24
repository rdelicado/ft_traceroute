/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_destination.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:29:16 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/24 12:41:05 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int is_only_spaces(const char *str)
{
	int i;

	if (!str)
		return 1;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && 
			str[i] != '\r' && str[i] != '\f' && str[i] != '\v')
			return (0);
		i++;
	}
	return 1;
}

void	validate_destination(t_args *args)
{
	struct in_addr	addr;

	if (args->target[0] == '\0')
	{
		printf("%s: No existe ninguna dirección asociada al nombre\n", args->target);
		printf("Cannot handle \"host\" cmdline arg `%s' on position 1 (argc 1)\n", args->target);
		exit(2);
	}
	else if (is_only_spaces(args->target))
	{
		printf("%s: Nombre o servicio desconocido\n", args->target);
		printf("Cannot handle \"host\" cmdline arg `%s' on position 1 (argc 1)\n", args->target);
		exit(2);
	}
	else if (strcmp(args->target, "255.255.255.255") == 0)
	{
		printf("traceroute to 255.255.255.255 (255.255.255.255), 30 hops max, 60 byte packets\n");
		printf("connect: Permiso denegado\n");
		exit(2);
	}
	
	/* Primero intentar como IP válida */
	if (check_if_ip(args->target, &addr))
		return ;
	
	/* Si no es IP, intentar resolver como hostname */
	if (find_hostname_ip(args->target, &addr))
		return ;
	
	/* No es ni IP ni hostname válido */
	printf("%s: Nombre o servicio desconocido\n", args->target);
	printf("traceroute: cannot resolve %s: Unknown host\n", args->target);
	exit(2);
	// checkear si es ip por puntos o hostname
}

