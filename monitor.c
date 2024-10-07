/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcouserg <fcouserg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:11:51 by fcouserg          #+#    #+#             */
/*   Updated: 2024/09/13 18:52:54 by fcouserg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_full(t_philo *philo)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	if (philo[0].nb_serving == -1)
		return (0);
	while (i < philo[0].total_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meal_count >= philo[i].nb_serving)
			full++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (full == philo[0].total_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead_flag = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

int	check_starved(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal >= philo->time_die
		&& philo->eating_flag == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philo)
{
	int		i;
	size_t	time;

	i = 0;
	while (i < philo[0].total_philos)
	{
		if (check_starved(&philo[i]) == 1)
		{
			pthread_mutex_lock(philo->write_lock);
			time = get_time() - philo->start_time;
			if (check_dead_flag(philo) == 0)
				printf("%ld %d %s\n", time, philo->id_philo, "died");
			pthread_mutex_unlock(philo->write_lock);
			pthread_mutex_lock(philo->dead_lock);
			*philo->dead_flag = 1;
			pthread_mutex_unlock(philo->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_if_dead(philo) == 1 || check_all_full(philo) == 1)
			break ;
		ft_usleep(1);
	}
	return (arg);
}
