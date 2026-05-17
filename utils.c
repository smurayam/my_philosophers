/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnnya <nnnya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:06:18 by nnnya             #+#    #+#             */
/*   Updated: 2026/05/17 19:09:00 by nnnya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = get_time() - philo->data->start_time;
	if (!check_if_dead(philo->data))
		printf("%lld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	check_if_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->data_lock);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->data_lock);
	return (dead);
}

void	ft_usleep(long long time_in_ms, t_data *data)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
	{
		if (check_if_dead(data))
			break ;
		usleep(500);
	}
}
