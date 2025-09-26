/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:53:49 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/26 11:06:05 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	display_hop(int ttl, t_icmp_response responses[], int num_probes)
{
	int		i;
	int		first_valid = -1;

	printf("%2d  ", ttl);

	// Buscar el primer probe válido para mostrar IP/nombre
	for (i = 0; i < num_probes; i++)
	{
		if (responses[i].valid)
		{
			first_valid = i;
			break;
		}
	}

	if (first_valid != -1)
	{
		// resolucion DNS inversa
		char *first_ip = inet_ntoa(responses[first_valid].from_addr);
		char host[NI_MAXHOST];
		struct sockaddr_in sa;
		ft_memset(&sa, 0, sizeof(sa));
		sa.sin_family = AF_INET;
		sa.sin_addr = responses[first_valid].from_addr;
		if (getnameinfo((struct sockaddr *)&sa, sizeof(sa),
				host, sizeof(host), NULL, 0, NI_NAMEREQD) == 0)
			printf("%s (%s)  ", host, first_ip);
		else
			printf("%s  ", first_ip);
	}
	else
	{
		printf("* ");
	}

	// Mostrar tiempos o asteriscos solo para los probes enviados
	for (i = 0; i < num_probes; i++)
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
	struct icmphdr		*icmp_hdr;
	struct iphdr		*ip_hdr;

	// Inicializar respuesta como inválida
	response->valid = 0;
	response->time_ms = -1;

	// Configurar select para timeout (5 segundos como traceroute real)
	FD_ZERO(&readfds);
	FD_SET(recv_sock, &readfds);
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;

	if (select(recv_sock + 1, &readfds, NULL, NULL, &timeout) > 0)
	{
		from_len = sizeof(from_addr);
		if (recvfrom(recv_sock, buffer, sizeof(buffer), 0,
			(struct sockaddr *)&from_addr, &from_len) > 0)
		{
			gettimeofday(&end_time, NULL);
			
			// Análisis del paquete ICMP
			ip_hdr = (struct iphdr *)buffer;
			icmp_hdr = (struct icmphdr *)(buffer + (ip_hdr->ihl * 4));
			
			// Filtrar solo respuestas ICMP relevantes para traceroute
			// Tipo 11: Time Exceeded (TTL expired)
			// Tipo 3: Destination Unreachable (incluyendo Port Unreachable)
			if (icmp_hdr->type != ICMP_TIME_EXCEEDED && icmp_hdr->type != ICMP_DEST_UNREACH)
				return (0); // Ignorar otros tipos de ICMP
			
			// Filtrar respuestas localhost (127.0.0.1)
			if (from_addr.sin_addr.s_addr == inet_addr("127.0.0.1"))
				return (0); // Ignorar localhost
			
			// Calcular tiempo de respuesta
			response->time_ms = calculate_time(start_time, &end_time);
			
			// Validar tiempo razonable (máximo 5000ms = timeout)
			if (response->time_ms > 5000.0 || response->time_ms < 0.0)
				response->time_ms = -1; // Marcar como inválido
			
			// Extraer IP del router que respondió
			response->from_addr = from_addr.sin_addr;
			response->icmp_type = icmp_hdr->type;
			response->valid = 1;
			
			return (1); // Éxito
		}
	}
	return (0); // Timeout o error
}