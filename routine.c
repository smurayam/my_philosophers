#include "philo.h"

// 哲学者の行動サイクル
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);

	while (1)
	{
		// ループの先頭でも死活チェックを行い、死んでいたら即座に終了
		if (check_if_dead(philo->data))
			break ;

		// 1. フォークを取る
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");

		// 2. 食べる
		print_status(philo, "is eating");
		
		pthread_mutex_lock(&philo->data->data_lock);
		philo->last_meal_time = get_time(); 
		philo->eat_count++; // ★ ここを追加：食事回数をカウントアップ
		pthread_mutex_unlock(&philo->data->data_lock);
		
		usleep(philo->data->time_to_eat * 1000);

		// ★ 重要：データレース対策
		// Monitorスレッドが読み取る last_meal_time を更新する際、衝突を防ぐためにロックをかけます
		pthread_mutex_lock(&philo->data->data_lock);
		philo->last_meal_time = get_time(); 
		pthread_mutex_unlock(&philo->data->data_lock);
		
		usleep(philo->data->time_to_eat * 1000);

		// フォークを置く
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// ★ 追加：食事が終わった直後にも、誰かが死んでいたらループを抜ける
		if (check_if_dead(philo->data))
			break ;

		// 3. 寝る
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);

		// 4. 考える
		print_status(philo, "is thinking");
	}
	return (NULL);
}

// スレッドの作成と開始
int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor; // ★ Monitorスレッド用の変数

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
	
	// ★ 監視スレッドの作成
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return (1);
	
	// ★ まず監視スレッドが終了する（＝誰かが死ぬ）のを待つ
	pthread_join(monitor, NULL);
	
	i = 0;
	// メインスレッドは全哲学者スレッドの終了を待つ
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
