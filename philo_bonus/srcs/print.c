/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:56:56 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:56:58 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_msg(char *str, t_ph *ph)
{
	size_t	timestamp;

	timestamp = get_time_ms() - ph->table->t_start;
	sem_wait(ph->sem_print);
	printf("%lu %d %s\n", timestamp, ph->id, str);
	sem_post(ph->sem_print);
}
