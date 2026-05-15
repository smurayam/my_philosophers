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

// プログラム終了時やエラー発生時に全てを安全に片付ける関数
void	destroy_all(t_data *data)
{
	int	i;

	// forksのメモリが確保されていれば、ミューテックスを破棄してfree
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
	// philosのメモリが確保されていればfree
	if (data->philos)
		free(data->philos);
	// 共通ミューテックスの破棄
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->data_lock);
}
