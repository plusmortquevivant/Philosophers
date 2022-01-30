/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:55:03 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:55:04 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <semaphore.h>

# define MSG_FORK	"has taken a fork"
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"
# define MSG_DEATH	"died"

# define SEM_NAME_FORKS	"ph_forks"
# define SEM_NAME_PRINT	"ph_print"
# define SEM_NAME_END	"ph_end"
# define SEM_NAME_FULL	"ph_fullness"
# define SEM_NAME_START "ph_start"
# define SEM_NAME_TAKE	"ph_take"
# define SEM_NAME_TIME	"ph_time"

typedef struct s_input {
	int		n_phs;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		n_to_eat;
}	t_input;

typedef struct s_table {
	t_input	input;
	size_t	t_start;
	sem_t	*sem_forks;
	sem_t	*sem_fullness;
	sem_t	*sem_print;
	sem_t	*sem_start;
	sem_t	*sem_end;
	sem_t	*sem_take;
}	t_table;

typedef struct s_ph {
	int		id;
	size_t	t_last_meal;
	size_t	t_start;
	sem_t	*sem_forks;
	sem_t	*sem_fullness;
	sem_t	*sem_print;
	sem_t	*sem_start;
	sem_t	*sem_end;
	sem_t	*sem_take;
	sem_t	*sem_time;
	t_table	*table;
}	t_ph;

int		parse_arg(const char *nptr);
int		init_table(int argc, char *argv[], t_table *table, pid_t **pids);
int		semaphore_create(const char *name, int value, sem_t **sem);
pid_t	start_ph(t_ph *ph);
int		end_simulation(t_table *table, pid_t *phs);
void	destroy_phs(int n, pid_t *phs);

size_t	get_time_ms(void);
void	ms_sleep(int t_ms);

void	print_msg(char *str, t_ph *ph);

void	ph_take_fork(t_ph *ph);
void	check_fullness(t_table *table, int meals_eaten);
void	ph_eat(t_ph *ph);
void	ph_sleep(t_ph *ph);
void	ph_think(t_ph *ph);

#endif
