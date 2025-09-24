/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:06:25 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/24 13:09:37 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H

#include <sys/time.h>
#include <stdint.h>
#include <netinet/in.h>

typedef struct s_args
{
	// opciones de flag
	int	show_help;

	// destino
	char	*target;
	struct in_addr	dest_addr;		/* Dirección IP en formato binario */
	char			*dest_ip;		/* Dirección IP en formato string */
	char			*hostname;		/* Hostname original (NULL si era IP) */
}	t_args;

#endif