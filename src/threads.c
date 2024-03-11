#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *pointer_philo)
{
	t_philo	*philo;

	philo = (t_philo *)pointer_philo;
	if (philo->id_philo % 2 == 0)
		ft_usleep(1);
	while (dead_loop(philo) == 0)
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer_philo);
}

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((philo->last_meal - get_time()) < philo->time_eat && philo->eating == 0)
	{
		*philo->dead = 1;
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nb_philo)
	{
		pthread_mutex_lock(philo[i].dead_lock);
		if (philo_dead(&philo[i]) == 1)
		{
			print_message(philo, "died");
			return (pthread_mutex_unlock(philo[i].dead_lock), 1);
		}
		pthread_mutex_unlock(philo[i].dead_lock);
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philo)
{
	int	i;
	int	finished_eating;

	if (philo[0].nb_serving == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	while (i < philo[0].nb_philo)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[0].nb_serving)
			finished_eating++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (finished_eating == philo[0].nb_philo)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	
	while (1)
		if (check_if_dead(philo) == 1 || check_if_all_ate(philo) == 1)
			break ;
	return (pointer);
}

void	thread_create(t_program *program)
{
	pthread_t	observer;
	int	i;

	if (pthread_create(&observer, NULL, &monitor, program->philo) != 0)
			printf("ERROR - OBSERVER pthread_create\n");
	i = 0;
	while (i < program->philo[0].nb_philo)
	{
		if (pthread_create(&program->philo[i].thread, NULL, &philo_routine, &program->philo[i]) != 0)
			printf("ERROR - PHILO pthread_create\n");
		i++;
	}
	if (pthread_join(observer, NULL) != 0)
			printf("ERROR - OBSERVER pthread_join\n");
	i = 0;
	while (i < program->philo[0].nb_philo)
	{
		if (pthread_join(program->philo[i].thread, NULL) != 0)
			printf("ERROR - PHILO pthread_join\n");
		i++;
	}
}
