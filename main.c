/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnnya <nnnya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:07:01 by nnnya             #+#    #+#             */
/*   Updated: 2026/05/17 19:08:27 by nnnya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int		i;
	long	val;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		val = ft_atol(argv[i]);
		if (val <= 0)
		{
			printf("Error: Invalid argument value\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	destroy_all(t_data *data)
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
		free(data->philos);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->data_lock);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != 0)
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argc, argv) != 0)
	{
		printf("Error: Initialization failed\n");
		destroy_all(&data);
		return (1);
	}
	printf("Initialization successful!\n");
	if (start_simulation(&data) != 0)
	{
		printf("Error: Thread creation failed\n");
		destroy_all(&data);
		return (1);
	}
	destroy_all(&data);
	return (0);
}
