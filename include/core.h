/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:38:49 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/26 11:19:19 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
#define CORE_H

#include "types.h"
#include <netinet/in.h>
#include <netdb.h>

/* Core functions */
void	print_help();
void	run_traceroute(t_args *args);

/* Parsing functions */
void	parse_arguments(t_args *args, int ac, char **av);
void	validate_destination(t_args *args);

/* Network functions */
int		check_if_ip(char *target, struct in_addr *out_addr);
int		find_hostname_ip(char *hostname, struct in_addr *out_addr);
int		convert_ip_binary(t_args *args);
int		create_send_socket();
int		create_recv_socket();
int 	set_socket_ttl(int sockfd, int ttl);

// icmp paquets
int		receive_icmp_response(int recv_sock, struct timeval *start_time, t_icmp_response *response, t_args *args);
void	display_hop(int ttl, t_icmp_response responses[], int num_probes);
double	calculate_time(struct timeval *start, struct timeval *end);

/* libft utilities */
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memset(void *s, int c, size_t n);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);



#endif