/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:06:25 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/25 11:20:37 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H

#include <sys/time.h>
#include <stdint.h>
#include <netinet/in.h>

typedef struct s_icmp_response
{
	double			time_ms;		/* Tiempo de respuesta en ms */
	struct in_addr	from_addr;		/* IP del router que respondió */
	int				icmp_type;		/* Tipo de mensaje ICMP */
	int				valid;			/* 1 si es válida, 0 si timeout */
}	t_icmp_response;

typedef struct s_args
{
	// opciones de flag
	int	show_help;

	// destino
	char			*target;		/* target argv sin procesar */
	struct in_addr	dest_addr;		/* Dirección IP en formato binario */
	char			*dest_ip;		/* Dirección IP en formato string */
	char			*hostname;		/* Hostname original (NULL si era IP) */
}	t_args;

#endif