/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcouserg <fcouserg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:33:58 by fcouserg          #+#    #+#             */
/*   Updated: 2024/09/13 18:49:26 by fcouserg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_philos(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->write_lock);
		if (philo->data->ph_created == philo->total_philos)
		{
			pthread_mutex_unlock(philo->write_lock);
			break ;
		}
		pthread_mutex_unlock(philo->write_lock);
		ft_usleep(philo->total_philos);
	}
}

void	eat_action(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->meal_lock);
	philo->eating_flag = 1;
	pthread_mutex_unlock(philo->meal_lock);
	print_message(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->meal_count++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating_flag = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	check_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead_flag == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	single_thread(t_philo *philo)
{
	print_message(philo, "has taken a fork");
	ft_usleep(philo->time_eat);
}

void	*manage_threads(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->total_philos == 1)
		single_thread(philo);
	else
	{
		pthread_mutex_lock(philo->write_lock);
		philo->data->ph_created++;
		pthread_mutex_unlock(philo->write_lock);
		wait_for_philos(philo);
		if (philo->id_philo % 2 == 0)
			ft_usleep(100);
		while (check_dead_flag(philo) == 0)
		{
			eat_action(philo);
			print_message(philo, "is sleeping");
			ft_usleep(philo->time_sleep);
			print_message(philo, "is thinking");
			ft_usleep(1);
		}
	}
	return (arg);
}
