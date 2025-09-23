/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:38:49 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/23 19:30:35 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
#define CORE_H

#include "types.h"

/* Core functions */
void	print_help();

/* Parsing functions */
void	parse_arguments(t_args *args, int ac, char **av);
void	validate_destination(t_args *args);
#endif