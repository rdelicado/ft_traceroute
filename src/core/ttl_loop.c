/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:09:12 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/26 09:30:15 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static void print_traceroute_header(t_args *args)
{
	if (args->hostname)
		printf("ft_traceroute to %s (%s), 30 hops max,  60 byte packets\n",
			args->hostname, args->dest_ip);
	else
		printf("ft_traceroute to %s, 30 hops max, 60 byte packets\n",
			args->dest_ip);
}

static int process_hop(int send_sock, int recv_sock, t_args *args, int ttl)
{
	struct sockaddr_in	dest_addr;
	char				buffer[60];
	int					i;
	int					responses;
	struct timeval		start_time;
	t_icmp_response		icmp_responses[3];
	int					reached_dest;

	// configurar direccion destino
	ft_memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_addr = args->dest_addr;
	dest_addr.sin_port = htons(33434 + ttl); // puerto UDP alto

	// Llenar buffer con datos (como traceroute real)
	ft_memset(buffer, 0x40 + ttl, sizeof(buffer));

	responses = 0;
	reached_dest = 0;
	for (i = 0; i < 3; i++)
	{
		// Pequeña pausa entre paquetes (100ms)
		if (i > 0)
			usleep(100000);

		// enviar paquete
		gettimeofday(&start_time, NULL);
		if (sendto(send_sock, buffer, sizeof(buffer), 0,
			(struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
		{
			icmp_responses[i].valid = 0; // Error
			continue;
		}

		// Recibir respuesta
		if (receive_icmp_response(recv_sock, &start_time, &icmp_responses[i]))
		{
			responses++;
			
			// Verificar si llegamos al destino (ICMP Port Unreachable = tipo 3)
			if (icmp_responses[i].icmp_type == 3)
			{
				reached_dest = 1;
			}
		}
	}
	
	// Mostrar resultados
	display_hop(ttl, icmp_responses);

	// Retornar 1 si llegamos al destino
	return (reached_dest);
}

static void ttl_loop(int send_sock, int recv_sock, t_args *args)
{
	int ttl;

	for (ttl = 1; ttl <= args->max_ttl; ttl++) // incluido (-m) <max_ttl>
	{
		//configurar TTL
		if (set_socket_ttl(send_sock, ttl) < 0)
			continue;

		// procesar el salto (envio, recepcion, display)
		if (process_hop(send_sock, recv_sock, args, ttl))
			break; // llegue al destino
	}
}

void run_traceroute(t_args *args)
{
	int	send_sock;
	int	recv_sock;

	send_sock = create_send_socket();
	if (send_sock < 0)
		exit(2);

	recv_sock = create_recv_socket();
	if (recv_sock < 0)
		exit(2);
	
	print_traceroute_header(args);
	ttl_loop(send_sock, recv_sock, args);
	
	close(send_sock);
	close(recv_sock);
}