/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:54:01 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:54:03 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

size_t	get_time_ms(void)
{
	struct timeval	tv;
	size_t			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	ms_sleep(int t_ms)
{
	size_t	start;
	size_t	end;

	start = get_time_ms();
	end = start + t_ms;
	while (get_time_ms() < end)
	{
		usleep(500);
	}
}
