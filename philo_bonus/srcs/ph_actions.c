/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:56:15 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:56:19 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ph_take_fork(t_ph *ph)
{
	sem_wait(ph->sem_forks);
	print_msg(MSG_FORK, ph);
}

void	check_fullness(t_table *table, int meals_eaten)
{
	if (meals_eaten == table->input.n_to_eat)
	{
		sem_post(table->sem_fullness);
	}
}

void	ph_eat(t_ph *ph)
{
	sem_wait(ph->sem_take);
	ph_take_fork(ph);
	ph_take_fork(ph);
	sem_post(ph->sem_take);
	sem_wait(ph->sem_time);
	ph->t_last_meal = get_time_ms();
	sem_post(ph->sem_time);
	print_msg(MSG_EAT, ph);
	ms_sleep(ph->table->input.t_to_eat);
}

void	ph_sleep(t_ph *ph)
{
	print_msg(MSG_SLEEP, ph);
	sem_post(ph->sem_forks);
	sem_post(ph->sem_forks);
	ms_sleep(ph->table->input.t_to_sleep);
}

void	ph_think(t_ph *ph)
{
	print_msg(MSG_THINK, ph);
	usleep(100);
}
