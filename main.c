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
	if (check_args(argc, argv) != 0)
		return (1);
	
	printf("Arguments are valid!\n");
	return (0);
}
