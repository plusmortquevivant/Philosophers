/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:55:51 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:55:54 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/error.h"

static void	*watcher_routine(void *arg)
{
	t_table	*table;
	int		i;
	int		n;

	table = (t_table *)arg;
	n = table->input.n_phs;
	i = 0;
	while (i < n)
	{
		sem_wait(table->sem_fullness);
		++i;
	}
	i = 0;
	while (i < n)
	{
		sem_wait(table->sem_fullness);
		++i;
	}
	sem_wait(table->sem_print);
	sem_post(table->sem_end);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_table		table;
	pid_t		*pids;
	pthread_t	watcher;

	if (!init_table(argc, argv, &table, &pids))
	{
		destroy_phs(table.input.n_phs, pids);
		return (ERROR_INPUT);
	}
	if (table.input.n_to_eat != -1)
	{
		if (pthread_create(&watcher, NULL, watcher_routine, &table))
		{
			destroy_phs(table.input.n_phs, pids);
			return (ERROR_THREAD);
		}
		pthread_detach(watcher);
	}
	if (!end_simulation(&table, pids))
	{
		return (ERROR_ENDSIM);
	}
	return (0);
}
