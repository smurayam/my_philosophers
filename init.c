#include "philo.h"

// フォーク（ミューテックス）の初期化
int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

// 哲学者の個別データの初期化
void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		// 哲学者の左側にあるフォークを割り当て
		data->philos[i].left_fork = &data->forks[i];
		// 哲学者の右側にあるフォークを割り当て（円卓なので最後は0番目に戻る）
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
}

// 全体データの初期化
int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = (int)ft_atol(argv[1]);
	data->time_to_die = (int)ft_atol(argv[2]);
	data->time_to_eat = (int)ft_atol(argv[3]);
	data->time_to_sleep = (int)ft_atol(argv[4]);
	if (argc == 6)
		data->must_eat_count = (int)ft_atol(argv[5]);
	else
		data->must_eat_count = -1;
	data->is_dead = 0;
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->data_lock, NULL) != 0)
		return (1);
	if (init_forks(data))
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (1);
	init_philos(data);
	return (0);
}
