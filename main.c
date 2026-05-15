#include "philo.h"

int	check_args(int argc, char **argv)
{
	int		i;
	long	val;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		val = ft_atol(argv[i]);
		if (val <= 0)
		{
			printf("Error: Invalid argument value\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	// 1. 引数のバリデーション
	if (check_args(argc, argv) != 0)
		return (1);
	
	// 2. 構造体のゼロクリア（超重要）
	// これにより、ポインタ(forksやphilos)が最初は確実にNULLになり、
	// 万が一初期化に失敗して destroy_all に入っても、安全に if(data->forks) で判定できます。
	memset(&data, 0, sizeof(t_data));

	// 3. 初期化処理
	if (init_data(&data, argc, argv) != 0)
	{
		printf("Error: Initialization failed\n");
		destroy_all(&data);
		return (1);
	}

	printf("Initialization successful!\n");

	// ==========================================
	// 4. TODO: ここにスレッドを作成して動かす処理が入ります
	// ==========================================

	// 5. プログラム正常終了時のクリーンアップ
	destroy_all(&data);
	return (0);
}
