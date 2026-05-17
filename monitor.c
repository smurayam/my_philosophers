/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnnya <nnnya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:57:38 by nnnya             #+#    #+#             */
/*   Updated: 2026/05/17 18:57:41 by nnnya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, int i)
{
	if (get_time() - data->philos[i].last_meal_time >= data->time_to_die)
	{
		data->is_dead = 1;
		pthread_mutex_unlock(&data->data_lock);
		pthread_mutex_lock(&data->print_lock);
		printf("%lld %d died\n", get_time() - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		all_ate = 1;
		while (++i < data->num_philos)
		{
			pthread_mutex_lock(&data->data_lock);
			if (check_death(data, i))
				return (NULL);
			if (data->must_eat_count == -1
				|| data->philos[i].eat_count < data->must_eat_count)
				all_ate = 0;
			pthread_mutex_unlock(&data->data_lock);
		}
		if (all_ate == 1)
		{
			pthread_mutex_lock(&data->data_lock);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->data_lock);
			return (NULL);
		}
		ft_usleep(1, data);
	}
	return (NULL);
}
