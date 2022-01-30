/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:56:30 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:56:34 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	kill_ph(t_table *table, int id)
{
	sem_wait(table->sem_print);
	printf("%lu %d %s\n", get_time_ms() - table->t_start, id, MSG_DEATH);
	sem_post(table->sem_end);
}

static void	*watcher_routine(void *arg)
{
	t_ph	*ph;
	t_table	*table;
	int		id;

	ph = (t_ph *)arg;
	table = ph->table;
	id = ph->id;
	while (1)
	{
		sem_wait(ph->sem_time);
		if ((int)(get_time_ms() - ph->t_last_meal) > table->input.t_to_die)
			break ;
		sem_post(ph->sem_time);
		usleep(2000);
	}
	kill_ph(table, id);
	return (NULL);
}

static void	ph_routine(t_ph *ph)
{
	int	meals_eaten;

	meals_eaten = 0;
	sem_wait(ph->sem_time);
	ph->t_last_meal = get_time_ms();
	sem_post(ph->sem_time);
	while (1)
	{
		ph_eat(ph);
		++meals_eaten;
		check_fullness(ph->table, meals_eaten);
		ph_sleep(ph);
		ph_think(ph);
	}
}

static int	init_ph_semaphores(t_ph *ph)
{
	char	sem_name_time[256];
	int		i;
	int		n;

	n = ph->id;
	i = -1;
	while (SEM_NAME_TIME[++i])
		sem_name_time[i] = SEM_NAME_TIME[i];
	sem_name_time[i++] = '_';
	while (n)
	{
		sem_name_time[i++] = n % 10 + '0';
		n /= 10;
	}
	if (!semaphore_create(SEM_NAME_FORKS, 0, &ph->sem_forks)
		|| !semaphore_create(SEM_NAME_PRINT, 0, &ph->sem_print)
		|| !semaphore_create(SEM_NAME_START, 0, &ph->sem_start)
		|| !semaphore_create(SEM_NAME_FULL, 0, &ph->sem_fullness)
		|| !semaphore_create(SEM_NAME_END, 0, &ph->sem_end)
		|| !semaphore_create(SEM_NAME_TAKE, 0, &ph->sem_take)
		|| !semaphore_create(sem_name_time, 1, &ph->sem_time))
		return (0);
	return (1);
}

pid_t	start_ph(t_ph *ph)
{
	pthread_t	watcher;
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		ph->sem_end = SEM_FAILED;
		if (!init_ph_semaphores(ph))
		{
			if (ph->sem_end != SEM_FAILED)
				sem_post(ph->sem_end);
			exit(1);
		}
		sem_wait(ph->sem_start);
		ph->t_last_meal = get_time_ms();
		if (pthread_create(&watcher, NULL, watcher_routine, ph))
			exit(sem_post(ph->sem_end));
		pthread_detach(watcher);
		ph_routine(ph);
		exit(0);
	}
	return (pid);
}
