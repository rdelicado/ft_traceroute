/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:08:38 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/24 12:32:25 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int	is_valid_ip_format(const char *dest, int *dots)
{
	int i;
	*dots = 0;

	for (i = 0; dest[i]; i++) {
		if (dest[i] == '.')
			(*dots)++;
		else if (dest[i] < '0' || dest[i] > '9')
			return 0;
	}
	return (*dots == 3);
}

int	check_if_ip(char *target, struct in_addr *out_addr)
{
	if (!target || target[0] == '\0')
		return 0;

	/* Check valid IP format */
	int dots;
	if (!is_valid_ip_format(target, &dots))
		return 0;

	/* Use inet_pton for final validation */
	struct in_addr addr;
	if (inet_pton(AF_INET, target, &addr) == 1) {
		if (out_addr) *out_addr = addr;
		return 1;
	}
	return 0;
}

int	find_hostname_ip(char *hostname, struct in_addr *out_addr)
{
    struct addrinfo		hints;
    struct addrinfo		*res;
    struct sockaddr_in	*sin;
    int					ret;

    if (!hostname || hostname[0] == '\0')
        return (0);

    /* Configurar hints para resolución DNS */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    /* Intentar resolver el hostname */
    ret = getaddrinfo(hostname, NULL, &hints, &res);
    if (ret != 0)
        return (0);

    /* Extraer la dirección IP */
    sin = (struct sockaddr_in *)res->ai_addr;
    if (out_addr)
        *out_addr = sin->sin_addr;

    freeaddrinfo(res);
    return (1);
}
