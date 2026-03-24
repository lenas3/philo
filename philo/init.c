/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:04:21 by asay              #+#    #+#             */
/*   Updated: 2026/03/23 21:09:59 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_main *main, char **argv)
{
	main->philo_num = ft_atoi(argv[1]);
	main->die_time = ft_atoi(argv[2]);
	main->eat_time = ft_atoi(argv[3]);
	main->sleep_time = ft_atoi(argv[4]);
	main->full_philos = 0;
	main->must_eat = -1;
	if (main->philo_num <= 0 || main->die_time <= 0
		|| main->eat_time < 0 || main->sleep_time < 0)
		return (1);
	if (argv[5])
	{
		main->must_eat = ft_atoi(argv[5]);
		if (main->must_eat <= 0)
			return (1);
	}
	return (0);
}

void	thread_create(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->philo_num)
	{
		main->philos[i].last_meal = main->start;
		pthread_create(&main->philos[i].thread, NULL,
			routine, (void *)&main->philos[i]);
		i++;
	}
}

void	thread_join(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->philo_num)
	{
		pthread_join(main->philos[i].thread, NULL);
		i++;
	}
}

int	init_philos(t_main *main)
{
	int	i;

	i = 0;
	main->philos = malloc((main->philo_num) * sizeof(t_philo));
	if (!main->philos)
		return (1);
	while (i < main->philo_num)
	{
		main->philos[i].p_id = i + 1;
		main->philos[i].left_fork = &main->forks[i];
		main->philos[i].right_fork = &main->forks[(i + 1) % main->philo_num];
		main->philos[i].data = main;
		main->philos[i].eat_num = 0;
		i++;
	}
	return (0);
}

int	init_forks(t_main *main)
{
	int	i;

	i = 0;
	main->forks = malloc((main->philo_num) * sizeof(pthread_mutex_t));
	if (!main->forks)
		return (1);
	while (i < main->philo_num)
	{
		pthread_mutex_init(&main->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&main->dead_mutex, NULL);
	pthread_mutex_init(&main->write_mutex, NULL);
	pthread_mutex_init(&main->meal_mutex, NULL);
	return (0);
}
