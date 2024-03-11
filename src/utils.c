#include "philo.h"

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (((*str > 8 && *str < 14) || *str == ' ') && *str)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str)
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * sign);
}

size_t	get_time(void)
{
	struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
		return (printf("ERROR - gettimeofday\n"), 1);
	return (tv.tv_usec);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}