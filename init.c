/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcouserg <fcouserg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:11:39 by fcouserg          #+#    #+#             */
/*   Updated: 2024/09/17 14:33:28 by fcouserg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_ph;

	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &manage_threads,
				&data->philo[i]) != 0)
			free_and_exit(data);
		i++;
	}
	if (data->total_philos > 100)
		ft_usleep(data->total_philos / 2);
	else
		ft_usleep(data->total_philos);
	pthread_create(&monitor_ph, NULL, &monitor, data->philo);
	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			free_and_exit(data);
		i++;
	}
	if (pthread_join(monitor_ph, NULL) != 0)
		free_and_exit(data);
}

void	distribute_forks(t_data *data, int i)
{
	pthread_mutex_t	*temp;

	data->philo[i].r_fork = &data->forks[i];
	if (i == 0)
		data->philo[i].l_fork = &data->forks[data->total_philos - 1];
	else
		data->philo[i].l_fork = &data->forks[i - 1];
	if (data->philo[i].id_philo == data->total_philos)
	{
		temp = data->philo[i].l_fork;
		data->philo[i].l_fork = data->philo[i].r_fork;
		data->philo[i].r_fork = temp;
	}
}

void	create_philos(t_data *data)
{
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->total_philos);
	if (data->philo == NULL)
	{
		free(data->forks);
		exit(0);
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	create_philos(data);
	while (i < data->total_philos)
	{
		data->philo[i].data = data;
		data->philo[i].id_philo = i + 1;
		data->philo[i].total_philos = data->total_philos;
		data->philo[i].time_die = data->time_die;
		data->philo[i].time_eat = data->time_eat;
		data->philo[i].time_sleep = data->time_sleep;
		data->philo[i].nb_serving = data->nb_serving;
		data->philo[i].eating_flag = 0;
		data->philo[i].meal_count = 0;
		data->philo[i].start_time = get_time();
		data->philo[i].last_meal = data->philo[i].start_time;
		data->philo[i].meal_lock = &data->meal_lock;
		data->philo[i].write_lock = &data->write_lock;
		data->philo[i].dead_lock = &data->dead_lock;
		data->philo[i].dead_flag = &data->dead_flag;
		distribute_forks(data, i);
		i++;
	}
	launch_threads(data);
}

void	init_data(t_data *data, t_philo *philo, char **argv)
{
	int	i;

	i = 0;
	data->philo = philo;
	data->total_philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nb_serving = ft_atoi(argv[5]);
	else
		data->nb_serving = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->total_philos);
	if (data->forks == NULL)
		exit(0);
	while (i < data->total_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->ph_created = 0;
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	data->dead_flag = 0;
}
