/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcouserg <fcouserg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:10:45 by fcouserg          #+#    #+#             */
/*   Updated: 2024/09/12 17:12:33 by fcouserg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	check_argc(argc);
	check_argv(argv);
	init_data(&data, philo, argv);
	init_philos(&data);
	if (data.dead_flag == 1 && data.philo->meal_count >= data.nb_serving
		&& data.nb_serving != -1)
		printf("All the philos ate their %d meals\n", data.nb_serving);
	free(data.philo);
	free(data.forks);
	return (0);
}
