/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smurayam <smurayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:19:35 by smurayam          #+#    #+#             */
/*   Updated: 2026/02/11 16:24:50 by smurayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	bool			dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	meal_lock;
	t_data			*data;
}	t_philo;

int		init_data(t_data *data, int ac, char **av);

int		start_simulation(t_data *data);

void	*philo_routine(void *pointer);

void	*monitor_routine(void *pointer);

void	print_status(t_philo *philo, char *str);
void	eat_routine(t_philo *philo);
void	sleep_routine(t_philo *philo);
void	think_routine(t_philo *philo);

int		ft_atoi(const char *str);
long	get_time(void);
int		ft_usleep(size_t milliseconds);
bool	check_dead_flag(t_data *data);

void	cleanup(t_data *data);
int		error_exit(char *str);

#endif