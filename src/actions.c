#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%ld %d %s\n", get_time(), philo->id_philo, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	dream(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_sleep);
}

void	think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork");
	// philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	print_message(philo, "is eating");
	philo->last_meal = get_time();
	philo->meals_eaten++;
	ft_usleep(philo->time_eat);	
	pthread_mutex_unlock(philo->meal_lock);
	// philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
