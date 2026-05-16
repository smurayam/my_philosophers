#include "philo.h"

// 監視スレッドのメイン処理
void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		all_ate = 1; // 初期値として「全員食べた」と仮定しておく
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->data_lock);
			// 1. 死亡チェック
			if (get_time() - data->philos[i].last_meal_time >= data->time_to_die)
			{
				data->is_dead = 1; // 死亡フラグ（兼シミュレーション停止フラグ）
				pthread_mutex_unlock(&data->data_lock);
				
				// 死亡メッセージの出力
				pthread_mutex_lock(&data->print_lock);
				printf("%lld %d died\n", get_time() - data->start_time, data->philos[i].id);
				pthread_mutex_unlock(&data->print_lock);
				return (NULL);
			}
			
			// 2. 食事回数チェック（オプション引数がある場合）
			if (data->must_eat_count == -1 || data->philos[i].eat_count < data->must_eat_count)
				all_ate = 0; // まだ目標回数に達していない人がいる
				
			pthread_mutex_unlock(&data->data_lock);
			i++;
		}
		
		// 3. 全員が目標回数食べ終わっていたら正常終了
		if (all_ate == 1)
		{
			pthread_mutex_lock(&data->data_lock);
			data->is_dead = 1; // 各スレッドのループを終わらせるためにフラグを立てる
			pthread_mutex_unlock(&data->data_lock);
			return (NULL);
		}
		
		// CPU負荷を下げるための微小スリープ
		usleep(1000);
	}
	return (NULL);
}
