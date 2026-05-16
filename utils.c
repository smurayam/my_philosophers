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

// 現在時刻をミリ秒単位で取得する
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// 状態を安全に出力する関数
void	print_status(t_philo *philo, char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = get_time() - philo->data->start_time;
	// is_dead の確認を安全に行う
	if (!check_if_dead(philo->data))
		printf("%lld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_lock);
}

// 誰かが死んでいるか安全に確認する関数
int	check_if_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->data_lock);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->data_lock);
	return (dead);
}
