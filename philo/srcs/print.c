/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:53:04 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:53:09 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	print_error(char *err_msg, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	printf("%s", err_msg);
	pthread_mutex_unlock(lock);
}

void	print_msg(char *str, t_ph *ph)
{
	t_table	*table;

	table = ph->table;
	pthread_mutex_lock(&table->m_print);
	if (is_finished(table))
		return ;
	printf("%lu %d %s\n", get_time_ms() - table->t_start, ph->id, str);
	pthread_mutex_unlock(&table->m_print);
}
