/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:02:21 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/24 13:12:47 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	convert_ip_binary(t_args *args)
{
	struct in_addr	addr;

	/* Intentar como IP primero */
    if (check_if_ip(args->target, &addr))
    {
        args->dest_addr = addr;
        args->dest_ip = inet_ntoa(addr);
        args->hostname = NULL;
        return (1);
    }

    /* Intentar resolver como hostname */
    if (find_hostname_ip(args->target, &addr))
    {
        args->dest_addr = addr;
        args->dest_ip = inet_ntoa(addr);
        args->hostname = args->target;
        return (1);
    }

    /* No se pudo resolver */
    printf("traceroute: cannot resolve %s: Unknown host\n", args->target);
    return (0);
}