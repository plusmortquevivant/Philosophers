/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:51:30 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:51:32 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define MSG_FORK	"has taken a fork"
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"
# define MSG_DEATH	"died"

typedef struct s_input {
	int		n_phs;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		n_to_eat;
}	t_input;

typedef struct s_table {
	t_input			input;
	int				ok;
	int				n_full;
	size_t			t_start;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_fullness;
	pthread_mutex_t	m_print;
}	t_table;

typedef struct s_ph {
	int				id;
	pthread_t		thread;
	size_t			t_last_meal;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	m_start;
	pthread_mutex_t	m_time;
	t_table			*table;
}	t_ph;

int		parse_arg(const char *nptr);
int		init_table(int argc, char *argv[], t_table *table, t_ph **phs);
int		create_threads(int n, t_ph *phs);
int		end_simulation(t_table *table, t_ph *phs);
int		is_finished(t_table *table);

size_t	get_time_ms(void);
void	ms_sleep(int t_ms);

void	print_msg(char *str, t_ph *ph);
void	print_error(char *err_msg, pthread_mutex_t *lock);

void	ph_take_fork(t_ph *ph, pthread_mutex_t *fork);
void	check_fullness(t_table *table, int meals_eaten);
void	ph_eat(t_ph *ph);
void	ph_sleep(t_ph *ph);
void	ph_think(t_ph *ph);

#endif
