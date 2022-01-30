/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:55:20 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:55:23 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	destroy_phs(int n, pid_t *phs)
{
	int	i;

	if (phs != NULL)
	{
		i = 0;
		while (i < n)
		{
			kill(phs[i], SIGKILL);
			++i;
		}
		free(phs);
	}
	sem_unlink(SEM_NAME_START);
	sem_unlink(SEM_NAME_END);
	sem_unlink(SEM_NAME_PRINT);
	sem_unlink(SEM_NAME_FORKS);
	sem_unlink(SEM_NAME_FULL);
	sem_unlink(SEM_NAME_TAKE);
}

int	end_simulation(t_table *table, pid_t *phs)
{
	int	n;

	sem_wait(table->sem_end);
	sem_wait(table->sem_end);
	n = table->input.n_phs;
	destroy_phs(n, phs);
	return (1);
}
