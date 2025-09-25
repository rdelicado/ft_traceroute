/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:53:49 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/25 11:20:37 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	display_hop(int ttl, t_icmp_response responses[3])
{
	int		i;
	char	*first_ip;

	printf("%2d  ", ttl);
	
	// Mostrar IP del primer router que respondió
	first_ip = NULL;
	for (i = 0; i < 3; i++)
	{
		if (responses[i].valid && !first_ip)
		{
			first_ip = inet_ntoa(responses[i].from_addr);
			printf("%s  ", first_ip);
			break;
		}
	}
	if (!first_ip)
		printf("*  ");

	// Mostrar tiempos
	for (i = 0; i < 3; i++)
	{
		if (responses[i].valid)
			printf("%.3f ms  ", responses[i].time_ms);
		else
			printf("* ");
	}
	printf("\n");
}

double calculate_time(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) * 1000.0) +
			((end->tv_usec - start->tv_usec) / 1000.0);
}

int	receive_icmp_response(int recv_sock, struct timeval *start_time, t_icmp_response *response)
{
	struct sockaddr_in	from_addr;
	socklen_t			from_len;
	char				buffer[512];
	fd_set				readfds;
	struct timeval		timeout;
	struct timeval		end_time;

	// Inicializar respuesta como inválida
	response->valid = 0;
	response->time_ms = -1;

	// Configurar select para timeout
	FD_ZERO(&readfds);
	FD_SET(recv_sock, &readfds);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	if (select(recv_sock + 1, &readfds, NULL, NULL, &timeout) > 0)
	{
		from_len = sizeof(from_addr);
		if (recvfrom(recv_sock, buffer, sizeof(buffer), 0,
			(struct sockaddr *)&from_addr, &from_len) > 0)
		{
			gettimeofday(&end_time, NULL);
			
			// Calcular tiempo de respuesta
			response->time_ms = calculate_time(start_time, &end_time);
			
			// Extraer IP del router que respondió
			response->from_addr = from_addr.sin_addr;
			
			// Análisis básico del tipo ICMP (simplificado por ahora)
			response->icmp_type = 11; // Time Exceeded por defecto
			response->valid = 1;
			
			return (1); // Éxito
		}
	}
	return (0); // Timeout o error
}