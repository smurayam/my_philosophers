#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

// 構造体の前方宣言（相互参照を可能にするため）
typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	data_lock;
	t_philo			*philos;
}	t_data;

long	ft_atol(const char *str);
int		check_args(int argc, char **argv);
int	init_data(t_data *data, int argc, char **argv);
void destroy_all(t_data *data);
long long get_time(void);
int	start_simulation(t_data *data);

#endif
