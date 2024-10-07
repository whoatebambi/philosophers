/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcouserg <fcouserg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:12:23 by fcouserg          #+#    #+#             */
/*   Updated: 2024/09/13 18:47:24 by fcouserg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("ERROR - gettimeofday\n");
		exit(0);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(200);
	return (0);
}

void	print_message(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	if (check_dead_flag(philo) == 0)
		printf("%ld %d %s\n", time, philo->id_philo, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	free_and_exit(t_data *data)
{
	int	i;

	i = 0;
	free(data->philo);
	free(data->forks);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->total_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	exit(0);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	i;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}
