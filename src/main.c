#include "philo.h"

int	check_valid_args(char **argv)
{
	if (ft_strisdigit(argv[1]) == 1 || ft_atoi(argv[1]) < 0 || ft_atoi(argv[1]) > PHILO_MAX)
		return(printf("ERROR - nb_philo\n"), 1);
	if (ft_strisdigit(argv[2]) == 1 || ft_atoi(argv[2]) < 0)
		return (printf("ERROR - time_die\n"), 1);
	if (ft_strisdigit(argv[3]) == 1 || ft_atoi(argv[3]) < 0)
		return (printf("ERROR - time_eat\n"), 1);
	if (ft_strisdigit(argv[4]) == 1 || ft_atoi(argv[4]) < 0)
		return (printf("ERROR - time_sleep\n"), 1);
	if (argv[5] && (ft_strisdigit(argv[5]) == 1 || ft_atoi(argv[5]) < 0))
		return (printf("ERROR - nb_serving\n"), 1);
	return (0);
}

// Initializing the program structure
void	init_program(t_program *program, t_philo *philo)
{
	program->philo = philo;
	program->dead_flag = 0;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	// printf("TEST\n");
}

// Initializing each philo structure
void	init_philo(t_philo *philo, t_program *program, pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id_philo = i + 1;
		philo[i].nb_philo = ft_atoi(argv[1]);
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_time();
		philo[i].dead = &program->dead_flag;
		philo[i].time_die = ft_atoi(argv[2]);
		philo[i].time_eat = ft_atoi(argv[3]);
		philo[i].time_sleep = ft_atoi(argv[4]);
		philo[i].start_time = get_time();
		philo[i].write_lock = &program->write_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[philo[i].nb_philo - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		// philo[i].l_fork = &forks[i];
		// philo[i].r_fork = &forks[(i + 1) % ft_atoi(argv[1])];
		if (argv[5])
			philo[i].nb_serving = ft_atoi(argv[5]);
		else
			philo[i].nb_serving = -1;
		i++;
	}
}

int	check_parsing(int argc)
{
	if (argc == 1 || argc != 5 || argc != 6)
	{
		printf("Please enter arguments.\nExample: ./philo 5 800 200 200 7\n\n");
		printf("5 — The number of philosophers\n");
		printf("800 — The time a philosopher will die if he doesn't eat\n");
		printf("200 — The time it takes a philosopher to eat\n");
		printf("200 — The time it takes a philosopher to sleep\n");
		printf("7 — (optional) Number of times all the philosophers need to eat before terminating the program\n");
		return (1);
	}
	return (0);
}

void	init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			philo[PHILO_MAX];
	t_program		program;
	pthread_mutex_t	forks[PHILO_MAX];

	if (check_parsing(argc) == 1)
		return (1);
	if (check_valid_args(argv) == 1)
		return (printf("ERROR - check_valid_args\n"), 1);
	init_program(&program, philo);
	init_philo(philo, &program, forks, argv);
	init_forks(forks, ft_atoi(argv[1]));
	thread_create(&program);
	return (0);
}
