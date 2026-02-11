/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smurayam <smurayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:27:50 by smurayam          #+#    #+#             */
/*   Updated: 2026/02/11 16:29:19 by smurayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' || num > INT_MAX)
		return (-1);
	return ((int)num);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < (long)milliseconds)
		usleep(500);
	return (0);
}

bool	check_dead_flag(t_data *data)
{
	bool	flag;

	pthread_mutex_lock(&data->dead_lock);
	flag = data->dead_flag;
	pthread_mutex_unlock(&data->dead_lock);
	return (flag);
}
