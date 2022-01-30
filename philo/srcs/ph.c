/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:52:35 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:52:38 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <error.h>

int	main(int argc, char *argv[])
{
	t_table	table;
	t_ph	*phs;

	if (!init_table(argc, argv, &table, &phs))
	{
		return (ERROR_INPUT);
	}
	if (!create_threads(table.input.n_phs, phs))
	{
		return (ERROR_THREAD);
	}
	while (!is_finished(&table))
	{
		usleep(500);
	}
	if (!end_simulation(&table, phs))
	{
		return (ERROR_ENDSIM);
	}
	return (0);
}
