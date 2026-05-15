#include "philo.h"

// 哲学者の行動サイクル
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// 偶数番目の哲学者の開始を少し遅らせて、デッドロック（全員が同時に左のフォークを取る状態）を防ぐ
	if (philo->id % 2 == 0)
		usleep(1000);

	// 誰かが死ぬまでループを続ける（後で死活判定フラグを組み込みます）
	while (1)
	{
		// 1. フォークを取る
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);

		// 2. 食べる
		printf("%lld %d is eating\n", get_time() - philo->data->start_time, philo->id);
		usleep(philo->data->time_to_eat * 1000); // 食べる時間待機

		// フォークを置く
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// 3. 寝る
		printf("%lld %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
		usleep(philo->data->time_to_sleep * 1000); // 寝る時間待機

		// 4. 考える
		printf("%lld %d is thinking\n", get_time() - philo->data->start_time, philo->id);
	}
	return (NULL);
}

// スレッドの作成と開始
int	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	// 哲学者の数だけスレッドを作成 [cite: 160]
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = get_time();
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	
	i = 0;
	// メインスレッドは全スレッドの終了を待つ
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
