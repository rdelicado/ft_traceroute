/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:51:29 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/25 09:31:19 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

// para envio de paquetes ttl
int create_send_socket()
{
	int sockfd;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf("ft_traceroute: socket: %s\n", strerror(errno));
		return (-1);
	}
	return (sockfd);
}

// para recepcion del paquete destino icmp reply
int	create_recv_socket()
{
	int sockfd;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		printf("ft_traceroute: socket: %s\n", strerror(errno));
		return (-1);
	}
	return (sockfd);
}

int set_socket_ttl(int sockfd, int ttl)
{
	if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
	{
		printf("ft_traceroute: setsockopt: %s\n", strerror(errno));
		return -1;
	}
	return 0;
}