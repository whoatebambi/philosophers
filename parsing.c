/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcouserg <fcouserg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:12:06 by fcouserg          #+#    #+#             */
/*   Updated: 2024/09/10 19:31:52 by fcouserg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_unsigned_int(char *str)
{
	long	nb;
	long	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb >= 0 && nb <= INT_MAX)
		return (1);
	return (0);
}

void	check_argc(int argc)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("Please enter arguments\nExample: ./philo 5 800 200 200 7\n\n");
		printf("5 — The number of philosophers\n");
		printf("800 — The time a philosopher will die if he doesn't eat\n");
		printf("200 — The time it takes a philosopher to eat\n");
		printf("200 — The time it takes a philosopher to sleep\n");
		printf("7 — (opt) Number of times all the philosophers need to eat\n");
		exit(0);
	}
}

void	check_argv(char **argv)
{
	if (!(is_unsigned_int(argv[1])))
		exit(0);
	if (!(is_unsigned_int(argv[2])))
		exit(0);
	if (!(is_unsigned_int(argv[3])))
		exit(0);
	if (!(is_unsigned_int(argv[4])))
		exit(0);
	if (argv[5] && (!(is_unsigned_int(argv[5]))))
		exit(0);
}
