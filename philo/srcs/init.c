/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:52:08 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:52:11 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	init_input(int argc, char *argv[], t_input *in)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of args.\n");
		return (0);
	}
	in->n_phs = parse_arg(argv[1]);
	in->t_to_die = parse_arg(argv[2]);
	in->t_to_eat = parse_arg(argv[3]);
	in->t_to_sleep = parse_arg(argv[4]);
	if (argc == 5)
		in->n_to_eat = -1;
	else
		in->n_to_eat = parse_arg(argv[5]);
	if (in->n_phs * in->t_to_die * in->t_to_eat
		* in->t_to_sleep * in->n_to_eat == 0)
	{
		printf("Error: wrong arguments.\n");
		return (0);
	}
	return (1);
}

static int	init_mutexes(t_table *table)
{
	int				n;
	pthread_mutex_t	*forks;

	n = table->input.n_phs;
	forks = malloc(n * sizeof(*forks));
	if (forks == NULL)
		return (0);
	while (n > 0)
	{
		if (pthread_mutex_init(&forks[--n], NULL) != 0)
			return (0);
	}
	table->m_forks = forks;
	if (pthread_mutex_init(&table->m_print, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->m_fullness, NULL) != 0)
		return (0);
	return (1);
}

static int	init_phs(int n, t_table *table, t_ph **phs)
{
	int		i;
	t_ph	*ps;

	ps = malloc(n * sizeof(*ps));
	if (ps == NULL)
		return (0);
	i = 0;
	while (i < n)
	{
		ps[i].id = i + 1;
		ps[i].first = &table->m_forks[i];
		ps[i].second = &table->m_forks[(i + 1) % n];
		if (pthread_mutex_init(&ps[i].m_start, NULL)
			|| pthread_mutex_init(&ps[i].m_time, NULL))
			return (0);
		ps[i].table = table;
		pthread_mutex_lock(&ps[i].m_start);
		++i;
	}
	*phs = ps;
	return (1);
}

int	init_table(int argc, char *argv[], t_table *table, t_ph **phs)
{
	if (!init_input(argc, argv, &table->input))
		return (0);
	if (!init_mutexes(table))
		return (0);
	if (!init_phs(table->input.n_phs, table, phs))
		return (0);
	table->ok = 1;
	table->n_full = 0;
	table->t_start = get_time_ms();
	return (1);
}
