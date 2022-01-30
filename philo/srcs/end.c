/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:51:53 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:51:56 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	destroy_phs(int n, t_ph *phs)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&phs[i].m_start);
		pthread_mutex_destroy(&phs[i].m_time);
		pthread_detach(phs[i].thread);
		++i;
	}
}

static void	destroy_forks(int n, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(forks + i);
		++i;
	}
}

int	end_simulation(t_table *table, t_ph *phs)
{
	int	n;

	n = table->input.n_phs;
	destroy_phs(n, phs);
	destroy_forks(n, table->m_forks);
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_fullness);
	return (1);
}
