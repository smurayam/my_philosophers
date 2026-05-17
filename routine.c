/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnnya <nnnya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:57:53 by nnnya             #+#    #+#             */
/*   Updated: 2026/05/17 19:04:36 by nnnya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks_and_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->data_lock);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->data_lock);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->data);
	while (1)
	{
		if (check_if_dead(philo->data))
			break ;
		if (take_forks_and_eat(philo))
			break ;
		if (check_if_dead(philo->data))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

static int	handle_thread_error(t_data *data, int count)
{
	int	j;

	pthread_mutex_lock(&data->data_lock);
	data->is_dead = 1;
	pthread_mutex_unlock(&data->data_lock);
	j = -1;
	while (++j < count)
		pthread_join(data->philos[j].thread, NULL);
	return (1);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time();
	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].last_meal_time = get_time();
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (handle_thread_error(data, i));
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return (handle_thread_error(data, i));
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}
