/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smurayam <smurayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:30:38 by smurayam          #+#    #+#             */
/*   Updated: 2026/02/11 16:30:44 by smurayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(char *str)
{
	printf("%s", str);
	return (1);
}

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->philos[i].meal_lock);
			i++;
		}
		free(data->philos);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
}
