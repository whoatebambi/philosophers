/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcouserg <fcouserg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:13:27 by fcouserg          #+#    #+#             */
/*   Updated: 2024/09/13 18:52:54 by fcouserg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INT_MAX 2147483647

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_data	*data;
	int				id_philo;
	int				total_philos;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				nb_serving;
	int				eating_flag;
	int				meal_count;
	size_t			last_meal;
	size_t			start_time;
	pthread_t		thread;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	int				*dead_flag;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

typedef struct s_data
{
	t_philo			*philo;
	int				total_philos;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				nb_serving;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	int				dead_flag;
	int				ph_created;
}					t_data;

// parsing.c
int					is_unsigned_int(char *str);
void				check_argv(char **argv);
void				check_argc(int argc);

// init.c
void				init_philos(t_data *data);
void				create_philos(t_data *data);
void				init_data(t_data *data, t_philo *philo, char **argv);
void				distribute_forks(t_data *data, int i);
void				launch_threads(t_data *data);

// threads.c
void				*manage_threads(void *arg);
void				wait_for_philos(t_philo *philo);
void				eat_action(t_philo *philo);
int					check_dead_flag(t_philo *philo);
void				single_thread(t_philo *philo);

// monitor.c
void				*monitor(void *arg);
int					check_if_dead(t_philo *philo);
int					check_starved(t_philo *philo);
int					check_all_full(t_philo *philo);

// utils.c
void				print_message(t_philo *philo, char *str);
int					ft_usleep(size_t milliseconds);
size_t				get_time(void);
void				free_and_exit(t_data *data);
int					ft_atoi(char *str);

#endif