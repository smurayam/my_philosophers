/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smurayam <smurayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:21:40 by smurayam          #+#    #+#             */
/*   Updated: 2026/02/11 16:24:50 by smurayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (error_exit("Error: Wrong number of arguments\n"));
	if (check_args(ac, av))
		return (error_exit("Error: Arguments must be numbers\n"));
	if (init_data(&data, ac, av) != 0)
		return (1);
	if (start_simulation(&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}