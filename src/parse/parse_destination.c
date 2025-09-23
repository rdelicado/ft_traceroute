/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_destination.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:29:16 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/23 19:38:39 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	validate_destination(t_args *args)
{
	if (args == NULL || args->target == NULL || args->target[0] == '\0')
	{
		printf("ft_traceroute: : No address associated with hostname\n");
		exit(2);
	}

	if (strcmp(args->target, "255.255.255.255") == 0)
	{
		printf("traceroute to 255.255.255.255 (255.255.255.255), 30 hops max, 60 byte packets\n");
		printf("connect: Permiso denegado\n");
		exit(2);
	}

	// checkear si es ip por puntos o hostname
}

