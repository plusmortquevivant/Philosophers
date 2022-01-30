/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:53:20 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:54:09 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <error.h>

int	is_finished(t_table	*table)
{
	return (!table->ok || (table->input.n_to_eat != -1
			&& table->n_full == table->input.n_phs));
}

static void	kill_ph(t_table *table, int id)
{
	if (is_finished(table))
		return ;
	pthread_mutex_lock(&table->m_print);
	printf("%lu %d %s\n", get_time_ms() - table->t_start, id, MSG_DEATH);
	table->ok = 0;
}

static void	*watcher_routine(void *arg)
{
	t_ph	*ph;
	t_table	*table;
	int		id;

	ph = (t_ph *)arg;
	table = ph->table;
	id = ph->id;
	while (!is_finished(table))
	{
		pthread_mutex_lock(&ph->m_time);
		if ((int)(get_time_ms() - ph->t_last_meal) > table->input.t_to_die)
			break ;
		pthread_mutex_unlock(&ph->m_time);
		usleep(2000);
	}
	kill_ph(table, id);
	return (NULL);
}

static void	*ph_routine(void *arg)
{
	pthread_t	watcher;
	t_ph		*ph;
	int			meals_eaten;

	ph = (t_ph *)arg;
	meals_eaten = 0;
	pthread_mutex_lock(&ph->m_start);
	pthread_mutex_lock(&ph->m_time);
	if (is_finished(ph->table))
		return (NULL);
	if (pthread_create(&watcher, NULL, watcher_routine, ph))
		return (NULL);
	pthread_detach(watcher);
	ph->t_last_meal = get_time_ms();
	pthread_mutex_unlock(&ph->m_time);
	while (!is_finished(ph->table))
	{
		ph_eat(ph);
		++meals_eaten;
		check_fullness(ph->table, meals_eaten);
		ph_sleep(ph);
		ph_think(ph);
	}
	pthread_mutex_unlock(&ph->m_start);
	return (NULL);
}

int	create_threads(int n, t_ph *phs)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (pthread_create(&phs[i].thread, NULL, ph_routine, phs + i))
		{
			print_error(ERRMSG_THREAD_CREATE, &phs[i].table->m_print);
			return (0);
		}
	}
	i = 0;
	while (i < n)
	{
		pthread_mutex_unlock(&phs[i].m_start);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < n)
	{
		pthread_mutex_unlock(&phs[i].m_start);
		i += 2;
	}
	return (1);
}
