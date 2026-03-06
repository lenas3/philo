/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:33:41 by asay              #+#    #+#             */
/*   Updated: 2026/03/06 17:03:33 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_main *main, t_philo *ptr)
{
	pthread_mutex_lock(ptr->left_fork);
	printing(main, ptr->philo_id, "has taken a fork.");
	sleep_carefully(main, main->die_time);
	printing(main, ptr->philo_id, "died.");
	pthread_mutex_lock(&main->dead_mutex);
	main->rudead = 1;
	pthread_mutex_unlock(&main->dead_mutex);
	pthread_mutex_unlock(ptr->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*ptr;
	t_main	*main;

	ptr = (t_philo *)arg;
	main = ptr->data;
	if (main->philo_num == 1)
	{
		one_philo(main, ptr);
		return (NULL);
	}
	if (ptr->philo_id % 2 == 0)
		usleep(800);
	while (1)
	{
		if (rudead_checker(main, 0))
			return (NULL);
		if (eating(main, ptr) == 0)
			return (NULL);
		if (thinking(main, ptr) == 0)
			return (NULL);
		if (sleeping(main, ptr) == 0)
			return (NULL);
	}
	return (NULL);
}

int	eating(t_main *main, t_philo *ptr)
{
	if (rudead_checker(main, 0))
		return (0);
	if (ptr->philo_id % 2 == 0)
	{
		pthread_mutex_lock(ptr->right_fork);
		printing(main, ptr->philo_id, "has taken a fork.");
		pthread_mutex_lock(ptr->left_fork);
		printing(main, ptr->philo_id, "has taken a fork.");
	}
	else
	{
		pthread_mutex_lock(ptr->left_fork);
		printing(main, ptr->philo_id, "has taken a fork.");
		pthread_mutex_lock(ptr->right_fork);
		printing(main, ptr->philo_id, "has taken a fork.");
	}
	pthread_mutex_lock(&main->meal_mutex);
	ptr->last_meal = convert_time();
	pthread_mutex_unlock(&main->meal_mutex);
	printing(main, ptr->philo_id, "is eating.");
	sleep_carefully(main, main->eat_time);
	pthread_mutex_lock(&main->meal_mutex);
	ptr->eat_num++;
	pthread_mutex_unlock(&main->meal_mutex);
	pthread_mutex_unlock(ptr->right_fork);
	pthread_mutex_unlock(ptr->left_fork);
	return (1);
}

int	thinking(t_main *main, t_philo *ptr)
{
	if (rudead_checker(main, 0))
		return (0);
	printing(main, ptr->philo_id, "is thinking.");
	if (main->philo_num % 2 != 0)
		sleep_carefully(main, (main->eat_time - 20));
	return (1);
}

int	sleeping(t_main *main, t_philo *ptr)
{
	if (rudead_checker(main, 0))
		return (0);
	printing(main, ptr->philo_id, "is sleeping.");
	sleep_carefully(main, main->sleep_time);
	return (1);
}
