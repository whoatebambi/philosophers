/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:20:06 by druina            #+#    #+#             */
/*   Updated: 2023/08/17 08:59:39 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

# define PHILO_MAX 300

typedef struct	s_philo
{
	pthread_t		thread;
	int				id_philo;	
	int				nb_philo;
	int				eating;
	int				*dead;		
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				nb_serving;
	size_t			start_time;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;

}				t_philo;

typedef struct	s_program
{
	t_philo			*philo;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	int				dead_flag;
}				t_program;

// Main functions
int			check_parsing(int argc);
int			check_valid_args(char **argv);
void		init_program(t_program *program, t_philo *philo);
void		init_philo(t_philo *philo, t_program *program, pthread_mutex_t *forks, char **argv);
void		*philo_routine(void *pointer_philo);
void		thread_create(t_program *program);

// // Initialization
// void				init_program(t_program *program, t_philo *philos);
// void				init_forks(pthread_mutex_t *forks, int philo_num);
// void				init_philos(t_philo *philos, t_program *program,
// 						pthread_mutex_t *forks, char **argv);
// void				init_input(t_philo *philo, char **argv);

// Threads
void			thread_create(t_program *program);
void			*philo_routine(void *pointer_philo);
int				dead_loop(t_philo *philo);
int				check_if_dead(t_philo *philo);
int				philo_dead(t_philo *philo);
int				check_if_all_ate(t_philo *philo);
void			*monitor(void *pointer);

// Actions
void			print_message(t_philo *philo, char *str);
void			eat(t_philo *philo);
void			dream(t_philo *philo);
void			think(t_philo *philo);

// // Monitor utils
// int					dead_loop(t_philo *philo);
// int					check_if_all_ate(t_philo *philos);
// int					check_if_dead(t_philo *philos);
// int					philosopher_dead(t_philo *philo, size_t time_to_die);

// Utils
int			ft_strisdigit(char *str);
int			ft_atoi(const char *str);
size_t		get_time(void);
int			ft_usleep(size_t milliseconds);

#endif
