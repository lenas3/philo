/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:49:09 by asay              #+#    #+#             */
/*   Updated: 2026/03/27 15:10:02 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	elapsed_time(t_main *main)
{
	long	elapsed;

	elapsed = convert_time() - main->start;
	return (elapsed);
}

long	convert_time(void)
{
	struct timeval	time;
	long			total_ms;

	total_ms = 0;
	gettimeofday(&time, NULL);
	total_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (total_ms);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;
	int		sign;

	i = 0;
	sum = 0;
	sign = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + (str[i] - '0');
		if ((sign == 1 && sum > 2147483647) || (sign == -1 && sum > 2147483648))
			return (0);
		i++;
	}
	return (sign * sum);
}

int	rudead_checker(t_main *main)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&main->dead_mutex);
	if (main->rudead == 1)
	{
		pthread_mutex_unlock(&main->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&main->dead_mutex);
	return (0);
}

void	printing(t_main *main, int p_id, char *str)
{
	if (rudead_checker(main))
		return ;
	pthread_mutex_lock(&main->write_mutex);
	if (rudead_checker(main))
	{
		pthread_mutex_unlock(&main->write_mutex);
		return ;
	}
	printf("%ld\t%d %s\n", elapsed_time(main), p_id, str);
	pthread_mutex_unlock(&main->write_mutex);
}
