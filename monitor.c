#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		all_ate = 1;		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->data_lock);
			if (get_time() - data->philos[i].last_meal_time >= data->time_to_die)
			{
				data->is_dead = 1;				pthread_mutex_unlock(&data->data_lock);
				
				pthread_mutex_lock(&data->print_lock);
				printf("%lld %d died\n", get_time() - data->start_time, data->philos[i].id);
				pthread_mutex_unlock(&data->print_lock);
				return (NULL);
			}
			
			if (data->must_eat_count == -1 || data->philos[i].eat_count < data->must_eat_count)
				all_ate = 0;				
			pthread_mutex_unlock(&data->data_lock);
			i++;
		}
		
		if (all_ate == 1)
		{
			pthread_mutex_lock(&data->data_lock);
			data->is_dead = 1;			pthread_mutex_unlock(&data->data_lock);
			return (NULL);
		}
		
		usleep(1000);
	}
	return (NULL);
}
