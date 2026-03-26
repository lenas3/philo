/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:33:41 by asay              #+#    #+#             */
/*   Updated: 2026/03/27 01:46:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_main *main, t_philo *ptr)
{
	pthread_mutex_lock(ptr->left_fork);
	printing(main, ptr->p_id, "has taken a fork.");
	sleep_carefully(main, main->die_time);
	printing(main, ptr->p_id, "died.");
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
	if (ptr->p_id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (rudead_checker(main, 0))
			return (NULL);
		if (eating(main, ptr) == 0)
			return (NULL);
		if (sleeping(main, ptr) == 0)
			return (NULL);
		if (thinking(main, ptr) == 0)
			return (NULL);
	}
	return (NULL);
}

int	eating(t_main *main, t_philo *ptr)
{
	if (ptr->p_id % 2 == 0 || ptr->p_id == main->philo_num)
	{
		pthread_mutex_lock(ptr->right_fork);
		printing(main, ptr->p_id, "has taken a fork.");
		pthread_mutex_lock(ptr->left_fork);
		printing(main, ptr->p_id, "has taken a fork.");
	}
	else
	{
		pthread_mutex_lock(ptr->left_fork);
		printing(main, ptr->p_id, "has taken a fork.");
		pthread_mutex_lock(ptr->right_fork);
		printing(main, ptr->p_id, "has taken a fork.");
	}
	printing(main, ptr->p_id, "is eating.");
	sleep_carefully(main, main->eat_time);
	pthread_mutex_lock(&main->meal_mutex);
	ptr->last_meal = convert_time();
	ptr->eat_num++;
	pthread_mutex_unlock(&main->meal_mutex);
	pthread_mutex_unlock(ptr->right_fork);
	pthread_mutex_unlock(ptr->left_fork);
	return (1);
}

int thinking(t_main *main, t_philo *ptr)
{
	long time_to_think;

	if (rudead_checker(main, 0))
		return (0);
	printing(main, ptr->p_id, "is thinking.");
	
	if (main->philo_num % 2 != 0)
	{
		time_to_think = (main->eat_time * 2) - main->sleep_time;
		if (time_to_think < 0)
			time_to_think = 0;
		sleep_carefully(main, time_to_think * 0.5); 
	}
	return (1);
}

int	sleeping(t_main *main, t_philo *ptr)
{
	if (rudead_checker(main, 0))
		return (0);
	printing(main, ptr->p_id, "is sleeping.");
	sleep_carefully(main, main->sleep_time);
	return (1);
}
