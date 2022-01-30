/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:52:51 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:52:53 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	ph_take_fork(t_ph *ph, pthread_mutex_t *fork)
{
	if (is_finished(ph->table))
		return ;
	pthread_mutex_lock(fork);
	print_msg(MSG_FORK, ph);
}

void	check_fullness(t_table *table, int meals_eaten)
{
	if (!is_finished(table) && meals_eaten == table->input.n_to_eat)
	{
		pthread_mutex_lock(&table->m_fullness);
		++(table->n_full);
		pthread_mutex_unlock(&table->m_fullness);
	}
}

void	ph_eat(t_ph *ph)
{
	if (ph->id % 2 == 0)
	{
		ph_take_fork(ph, ph->first);
		ph_take_fork(ph, ph->second);
	}
	else
	{
		ph_take_fork(ph, ph->second);
		ph_take_fork(ph, ph->first);
	}
	if (is_finished(ph->table))
		return ;
	pthread_mutex_lock(&ph->m_time);
	ph->t_last_meal = get_time_ms();
	pthread_mutex_unlock(&ph->m_time);
	print_msg(MSG_EAT, ph);
	ms_sleep(ph->table->input.t_to_eat);
}

void	ph_sleep(t_ph *ph)
{
	if (is_finished(ph->table))
		return ;
	print_msg(MSG_SLEEP, ph);
	pthread_mutex_unlock(ph->second);
	pthread_mutex_unlock(ph->first);
	ms_sleep(ph->table->input.t_to_sleep);
}

void	ph_think(t_ph *ph)
{
	if (is_finished(ph->table))
		return ;
	print_msg(MSG_THINK, ph);
	usleep(100);
}
